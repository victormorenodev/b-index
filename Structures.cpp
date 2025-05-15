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

int Node:: getLine() {
    return line;
}

int Node:: getFatherLine() {
    return fatherLine;
}

Node::~Node() = default;

NodeType Node::getType() const {
    return type;
}

vector<int>& Node::getKeys() {
    return keys;
}

void Node::setFatherLine(int newFather) {
    this->fatherLine = newFather;
}



LeafNode::LeafNode(int line, int fatherLine, int nPts, int neighbor)
    : Node(line, fatherLine, nPts, NodeType::LEAF), neighbor(neighbor)
{
    csvPos.resize(nPts - 1);
}

LeafNode::LeafNode(int line, int fatherLine, int nPts, vector<int> keys, vector<int> csvPos, int neighbor)
    : Node(line, fatherLine, nPts, NodeType::LEAF), csvPos(csvPos), neighbor(neighbor) {
    this->keys = keys;
}

bool LeafNode::isLeaf() const {
    return true;
}

std::vector<int>& LeafNode::getCsvPos(){
    return csvPos;
}

int LeafNode::getNeighbor() {
    return neighbor;
}

void LeafNode::setNeighbor(int new_neighbor) {
    neighbor = new_neighbor;
    return;
}


InternalNode::InternalNode(int line, int fatherLine, int nPts)
    : Node(line, fatherLine, nPts, NodeType::INTERNAL)
{
    children.resize(nPts);
}

InternalNode::InternalNode(int line, int fatherLine, int nPts, vector<int> keys, vector<int> children)
    : Node(line, fatherLine, nPts, NodeType::INTERNAL), children(children) {
    this->keys = keys;
}

bool InternalNode::isLeaf() const {
    return false;
}

std::vector<int>& InternalNode::getChildren(){
    return children;
}