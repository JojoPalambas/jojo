#include <string>
#include "file-writer.hh"
#include "file-reader.hh"
#include "bwt.hh"
#include "rle.hh"

int main()
{
    FileReader fr(std::string("inputfile.txt"));
    FileWriter fw(std::string("outputfile.txt"));

    BWT bwt('%'); //the constructor of BWT takes the end-of-file
    //special character as argument

    RLE rle('@'); //the constructor of RLE takes its special
    //character as argument too

    const std::string content = fr.read();

    const std::string transformed = bwt.perform(content);
    const std::string output = rle.perform(transformed);
    fw.write(output);
}
