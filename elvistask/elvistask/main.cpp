#include "filesparser.h"
#include "profile.h"

using namespace std;

void TestSpeedMultiThread() {
    const size_t counts = 1000;
    for (size_t i = 0; i < counts; ++i) {
        Parser::FilesParser manager("B:\\dev\\elvistask\\elvistask\\files", "output.txt");
        manager.MultiThreadParse();
    }
}

void TestSpeedSingleThread() {
    const size_t counts = 1000;
    for (size_t i = 0; i < counts; ++i) {
        Parser::FilesParser manager("B:\\dev\\elvistask\\elvistask\\files", "output.txt");
        manager.SingleThreadParse();
    }
}

int main()
{   
    try {
            {
                LOG_DURATION("Test Speed of Single-Thread Parsing");
                TestSpeedSingleThread();
            }

            {
                LOG_DURATION("Test Speed of Multi-Thread Parsing");
                TestSpeedMultiThread();
            }
        
            cout << "Enter directory path and output path:\n";
            string catalog, outfile;
            cin >> catalog >> outfile;
            Parser::FilesParser manager(catalog, outfile);
            manager.SingleThreadParse();
       
    }
    catch(exception& e ) {
        cerr << e.what();
    }


}