#ifndef NODE_H
#define NODE_H

#include <QObject>
#include <QFileInfo>
#include <QList>
#include <QDir>

class Node : public QObject
{
    Q_OBJECT

public:
    explicit Node(QFileInfo nodeData, QObject *parent = nullptr);
    int getNodeCount() const;
    void addChild(Node* child);
    QFileInfo getNodeData() const;
    void setNodeData(QFileInfo nodeData);
    QList<Node*>* getChildren() const;
    int getFileCount() const;
    int getDirCount() const;
    /*
     * please destruct the tree manually by this func
     * @param input: the root of the tree
     */
    static void deleAll(Node* root);
    /*
     * please ues this func to create tree.
     * @param input: the dir of the file tree.
     * @return the ptr of the tree. YOU SHOULD use deleALL(ptr) later.
     */
    static Node* createFileTree(QString path);

private:
    QFileInfo nodeData;
    QList<Node*>* children;
    void deleSub();
    static void createfiletree(Node* root);

signals:

public slots:

};

#endif // NODE_H
