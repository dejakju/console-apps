/*
 * Name:    Goran Todorovic (dejakju@gmail.com)
 * Date:    2023-05-02
 * Update:  2023-05-02
 * Desc.:   Writes any textfile to 'stdout' in a typewriter fashion
 */

#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>

#include <unistd.h>     // Standard 'C'


// Prints the 'usage' to stdout
static void usage(const char *argv0)
{
    std::cout << "Usage: "
        << argv0
        << " [-f filename]"
        << " [-t milliseconds]"
        << std::endl;
    exit(1);
}

// Checks a string if it is numeric
static bool is_numeric(std::string s)
{
    for (int i = 0; i < s.length(); i++)
        if (isdigit(s[i]) == false)
            return false;
    return true;
}

int main(int argc, char *argv[])
{
    int opt;
    std::string fileName = "credits.txt";       // set the value of the -f parameter (default: credits.txt)
    std::chrono::milliseconds mSeconds{150};    // set the value of the -t parameter (default: 150ms)

    // Main parameter/options loop with some validation
    while ((opt = getopt(argc, argv, "f:t:")) != -1)
    {
        switch (opt)
        {
        case 'f':
            {
                // If the filename is less than one character, quit
                std::istringstream iss(optarg);
                if (iss.str().length() < 1)
                    usage(argv[0]);

                iss >> fileName;
            }
            break;
        case 't':
            {

                std::istringstream iss(optarg);
                if (!is_numeric(iss.str()))
                {
                    std::cout << "ERROR: -t parameter needs to be a valid integer" << std::endl;
                    usage(argv[0]);
                }
                else
                {
                    int number;
                    iss >> number;
                    mSeconds = std::chrono::milliseconds(number);
                }
            }
            break;
        default: /* '?' */
            usage(argv[0]);
        }
    }

    // If there are any (unknown) additional arguments, bail out
    if (optind != argc)
    {
        std::cerr << "ERROR: wrong number of arguments" << std::endl;
        usage(argv[0]);
    }

    // If we reach this point, almost all checks are done
    std::ifstream file;
    file.open(fileName);

    // Check for a valid file, if it fails, quit
    if (file.fail())
    {
        std::cerr << "ERROR: couldn't open file \'" << fileName << "\'" << std::endl;
        exit(1);
    }

    // Read all contents of the file into a buffer and convert it to a 'std::string'
    std::stringstream buffer;
    std::string file_content;
    buffer << file.rdbuf();
    file_content = buffer.str();

    // Traverse the whole string step by step and put the main thread to sleep for the specified amount of time
    for (long unsigned int i = 0; i < file_content.length(); i++)
    {
        std::cout << file_content[i];
        std::this_thread::sleep_for(mSeconds);
        // This next line is very(!) important
        std::cout.flush();
    }

    // Add a newline character at the very end, if neccessary
    if (file_content.at(file_content.length() - 1) != '\n')
        std::cout << std::endl;

    // We're done, so close the file and return with a smile on your face
    file.close();
    return 0;
}
