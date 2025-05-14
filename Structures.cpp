#include "Structures.h"

Operation::Operation(Instruction o, int val) {
    instruction = o;
    x = val;
}

Instruction Operation::getInstruction() const {
    return instruction;
}

int Operation::getX() const {
    return x;
}



Node::Node(int line, int fatherLine, int nPts, NodeType type)
    : line(line), fatherLine(fatherLine), nPts(nPts), type(type)
{
    keys.resize(nPts - 1);
}

Node::~Node() = default;

NodeType Node::getType() const {
    return type;
}

const std::vector<int>& Node::getKeys() const {
    return keys;
}



LeafNode::LeafNode(int line, int fatherLine, int nPts, int neighbor)
    : Node(line, fatherLine, nPts - 1, NodeType::LEAF), neighbor(neighbor)
{
    csvPos.resize(nPts - 1);
}

bool LeafNode::isLeaf() const {
    return true;
}

const std::vector<int>& LeafNode::getCsvPos() const {
    return csvPos;
}

int LeafNode::getNeighbor() const {
    return neighbor;
}



InternalNode::InternalNode(int line, int fatherLine, int nPts)
    : Node(line, fatherLine, nPts - 1, NodeType::INTERNAL)
{
    children.resize(nPts);
}

bool InternalNode::isLeaf() const {
    return false;
}

const std::vector<int>& InternalNode::getChildren() const {
    return children;
}