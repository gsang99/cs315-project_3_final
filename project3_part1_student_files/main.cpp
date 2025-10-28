#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include <optional>
#include <iomanip>


#include "Priorityqueue.h"
#include "BinSearchTree.h"
#include "Scanner.hpp"
#include "utils.hpp"
#include "HuffmanTree.h"


//helper function
bool compareFreqDesc(const std::pair<std::string, int>& a,
                     const std::pair<std::string, int>& b) {
    if (a.second != b.second) {
        return a.second > b.second;  // freq descending
    }
    return a.first < b.first;  // word ascending (tie-break)
}

int main(int argc, char *argv[]) {

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }

    //changed multiple things to make the input able to be more flexible and take in
    const std::string inputFileName = std::string(argv[1]);

    std::filesystem::path inputPath = inputFileName;

    std::filesystem::path dirName = inputPath.parent_path();
    std::string inputFileBaseName = inputPath.stem().string();

    // build the path to the .tokens output file.
    std::filesystem::path wordTokensFileName = dirName / (inputFileBaseName + ".tokens");


    //buid path for .freq output files
    std::filesystem::path freqTokensFileName = dirName / (inputFileBaseName + ".freq");

    //buid path for .hdr output files
    std::filesystem::path hdrTokensFileName = dirName / (inputFileBaseName + ".hdr");


    //buid path for .code output files
    std::filesystem::path codeTokensFileName = dirName / (inputFileBaseName + ".code");


    // The next several if-statement make sure that the input file, the directory exist
    // and that the output file is writeable.
     if( error_type status; (status = regularFileExistsAndIsAvailable(inputFileName)) != NO_ERROR )
        exitOnError(status, inputFileName);


    if (error_type status; (status = directoryExists(dirName.string())) != NO_ERROR )
        exitOnError(status, dirName.string());

    if (error_type status; (status = canOpenForWriting(wordTokensFileName.string())) != NO_ERROR)
        exitOnError(status, wordTokensFileName.string());


    //constructor for input file
    Scanner fileToWords(inputPath);
    std::vector<std::string> words;


    if( error_type status; (status = fileToWords.tokenize(words)) != NO_ERROR)
	    exitOnError(status, inputFileName);

    if (error_type status; (status = writeVectorToFile(wordTokensFileName.string(), words)) != NO_ERROR)
        exitOnError(status, wordTokensFileName.string());


    //creating the parts of the main for part 2
    //make the bst
    BinSearchTree bst;
    bst.bulkInsert(words);

    //this will collect all of the counts
    std::vector<std::pair<std::string, int>> counts;
    bst.inorderCollect(counts);

    //doing the run down of everything that needs to be printed

    //height
    unsigned height = bst.height();

    //unique words
    int unique = bst.size();

    //total tokens
    int tokens = words.size();

    //min frequency
    int minFreq = 0;

    //max frequency
    int maxFreq = 0;

    //checking if counts is empty
    if (!counts.empty()) {
        minFreq = counts.front().second;
        maxFreq = counts.front().second;
        for (int i = 0; i < counts.size(); i++)
        {
            auto currPair = counts.at(i);

            //then we assign that bad boy to another variable to grab the frequency
            int f = currPair.second;
            if (f < minFreq) minFreq = f;
            if (f > maxFreq) maxFreq = f;
        }
    }

    // Print to stdout (exact labels)
    std::cout << "BST height: " << height << "\n";
    std::cout << "BST unique words: " << unique << "\n";
    std::cout << "Total tokens: " << tokens << "\n";
    std::cout << "Min frequency: " << (counts.empty() ? 0 : minFreq) << "\n";
    std::cout << "Max frequency: " << (counts.empty() ? 0 : maxFreq) << "\n";


    //freq file
    std::ofstream freqFile(freqTokensFileName);
    if (!freqFile.is_open()) {
        std::cerr << "Error: Unable to open " << freqTokensFileName << " for writing\n";
        return 1;
    }

    std::sort(counts.begin(), counts.end(), compareFreqDesc);

    for (int i = 0; i < counts.size(); i++) {
        std::string word = counts.at(i).first;
        int freq = counts.at(i).second;
        freqFile << std::setw(10) << freq << " " << word << "\n";
    }

    freqFile.close();

    //making the huffman tree
    HuffmanTree tree = HuffmanTree::buildFromCounts(counts);

    std::ofstream hdrFile(hdrTokensFileName);

    // Call writeHeader
        error_type err = tree.writeHeader(hdrFile);

    // Check for errors
    if (err != NO_ERROR) {
        std::cerr << "Error writing header file!" << std::endl;
        return err;
    }

// Close the file
    hdrFile.close();

    // Encode the tokens
    std::ofstream codeFile(codeTokensFileName);
    if (!codeFile.is_open()) {
        std::cerr << "Error: Unable to open " << codeTokensFileName << " for writing\n";
        return 1;
    }

    error_type encodeErr = tree.encode(words, codeFile, 80);
    if (encodeErr != NO_ERROR) {
        std::cerr << "Error encoding file!" << std::endl;
        return encodeErr;
    }

    codeFile.close();


    return 0;
}
