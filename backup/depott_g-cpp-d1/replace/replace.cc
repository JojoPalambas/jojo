#include "replace.hh"

void replace(const std::string& input_filename,
             const std::string& output_filename,
             const std::string& src_token,
             const std::string& dst_token)
{
    std::ifstream file_in;
    std::ofstream file_out;

    std::string line;
    std::string token;

    file_in.open(input_filename);
    if (file_in.is_open())
    {
        std::cerr << "Cannot open input file" << std::endl;
        return;
    }

    file_out.open(output_filename);
    if (file_out.is_open())
    {
        std::cerr << "Cannot open output file" << std::endl;
        return;
    }

    while (!(getline(file_in, line)).eof())
    {
        stringstream ss;
        ss << line;
        while ((ss >> token).good())
        {
            if (token.compare(src_token))
                file_out << dst_token;
            else
                file_out << token;
        }
        file_out << std::endl;
    }

    file_in.close();
    file_out.close();
}

int main ()
{
    replace("input.txt", "output.txt", "totor", "tartare");
}
