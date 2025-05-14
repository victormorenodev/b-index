#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <vector>

using namespace std;

enum class Instruction {
    INC,
    BUS,
    FLH,
    INVALID
};

class Operation {
    private:
        Instruction instruction;
        int x;

    public:
        Operation(Instruction o, int val);

        Instruction getInstruction() const;

        int getX() const;
    };

    enum class NodeType {
        INTERNAL,
        LEAF
    };

    
class Node {
    protected:
        int line;
        int fatherLine;
        std::vector<int> keys;
        NodeType type;
        int nPts;
    
    public:
        Node(int line, int fatherLine, int nPts, NodeType type)
            : line(line), fatherLine(fatherLine), nPts(nPts), type(type)
        {
            keys.resize(nPts-1);
        }
    
        virtual ~Node() = default;
    
        NodeType getType() const { return type; }
        const vector<int>& getKeys() const { return keys; }
        virtual bool isLeaf() const = 0;
    };

class LeafNode : public Node {
    private:
        std::vector<int> csvPos;
        int neighbor;
    
    public:
        LeafNode(int line, int fatherLine, int nPts, int neighbor)
            : Node(line, fatherLine, nPts - 1, NodeType::LEAF), neighbor(neighbor)
        {
            csvPos.resize(nPts - 1); // mesmo número de posições que chaves
        }
    
        bool isLeaf() const override { return true; }
    
        const vector<int>& getCsvPos() const { return csvPos; }
        int getNeighbor() const { return neighbor; }
    };

class InternalNode : public Node {
    private:
        std::vector<int> children;
    
    public:
        InternalNode(int line, int fatherLine, int nPts)
            : Node(line, fatherLine, nPts - 1, NodeType::INTERNAL)
        {
            children.resize(nPts); // N ponteiros
        }
    
        bool isLeaf() const override { return false; }
    
        const vector<int>& getChildren() const { return children; }
    };

#endif