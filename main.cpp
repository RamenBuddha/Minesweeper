#include "windows.h"
using namespace std;

int main() {
    pair<bool,string> toCatch = welcomeWindow();
    if (toCatch.first) {
        gameWindow(toCatch.second);
    }
    return 0;
}