#include "node.h"

Node::Node(QFileInfo nodeData, QObject *parent) : QObject(parent)
{
    this->children = new QList<Node*>();
    setNodeData(nodeData);
}

Node* Node::createFileTree(QString path)
{
    QFileInfo rootInfo(path);
    if (!rootInfo.isDir())
        return nullptr;
    Node* root = new Node(rootInfo);
    createfiletree(root);
    return root;
}

void Node::createfiletree(Node* root)
{
    QDir dir(root->getNodeData().absoluteFilePath());
    dir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
    QFileInfoList folder_list = dir.entryInfoList();

    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    QFileInfoList file_list = dir.entryInfoList();

    for(QFileInfo folderInfo : folder_list)
    {
        Node* child = new Node(folderInfo);
        root->addChild(child);
        createfiletree(child);
    }
    for(QFileInfo fileInfo : file_list)
    {
        root->addChild(new Node(fileInfo));
    }
}

void Node::deleAll(Node* root)
{
    root->deleSub();
    delete root;
    root = nullptr;
}

void Node::deleSub()
{
    for (Node* child : *children) {
        child->deleSub();
        delete child;
        child = nullptr;
    }
    delete children;
    children = nullptr;
}

void Node::setNodeData(QFileInfo nodeData) {
    this->nodeData = nodeData;
}

void Node::addChild(Node* child) {
    this->children->append(child);
}

QFileInfo Node::getNodeData() const {
    return nodeData;
}

QList<Node*>* Node::getChildren() const {
    return children;
}

int Node::getNodeCount() const {
    int sum = 1;
    for (Node* child : *children) {
        sum += child->getNodeCount();
    }
    return sum;
}
int Node::getFileCount() const {
    int sum = 0;
    if (nodeData.isFile())
        sum = 1;
    for (Node* child : *children) {
        sum += child->getFileCount();
    }
    return sum;
}
int Node::getDirCount() const {
    int sum = 0;
    if (nodeData.isDir())
        sum = 1;
    for (Node* child : *children) {
        sum += child->getDirCount();
    }
    return sum;
}
