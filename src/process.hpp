#include "process.h"
#include <string>
#include <map>
#include <vector>

using std::string;

class Node {
    private:
        std::map<int, int> lookup;
        std::vector<Node*> inputs;
        std::vector<Node*> outputs;
    public:
        Node();
        virtual ~Node();
};