#include "FamilyTree.hpp"

using namespace family;


Node::Node(std::string name, int rank, std::string relation, std::string childName) {
    this->name = name;
    this->mother = nullptr;
    this->father = nullptr;
    this->rank = rank;
    this->relation = relation;
    this->childName = childName;

}

Node *Node::getFather() {
    return this->father;

}

std::string Node::getChildName() {
    return this->childName;

}


std::string Node::getRelation() {
    return this->relation;
}

Node *Node::getMother() {
    return this->mother;
}

int &Node::getRank() {
    return this->rank;
}

void Node::setMother(std::string name, int rank, std::string relation, std::string childName) {
    this->mother = new Node(name, rank, relation, childName);

}

void Node::setFather(std::string name, int rank, std::string relation, std::string childName) {
    this->father = new Node(name, rank, relation, childName);

}

void Node::setName(std::string name) {
    this->name = name;
}

std::string Node::getName() {
    return this->name;
}


Tree::Tree(std::string root) {
    this->root = new Node(root, 0, "me", "none");


}

Tree::~Tree() {
    deleteTree(root);

}

void Node::setFatherNull(){
    this->father= nullptr;
}

void Node:: setMotherNull(){
    this->mother= nullptr;
}

void Tree::deleteTree(Node *root) {

    if (root != nullptr) {

        deleteTree(root->getFather());
        deleteTree(root->getMother());
        // std::cout << "Deleting node: " << root->getName() << std::endl;
        delete (root);
        if (root->getFather() != nullptr)
            root->setFatherNull();
        if (root->getMother() != nullptr)
            root->setMotherNull();


    }



}

Tree &Tree::addFather(std::string name, std::string parent) {

    if (this->root != nullptr) {
        Node *temp = search(name, this->root, false);
        if (temp != nullptr) { // means the child was found
            if (temp->getFather() == nullptr) {
                temp->setFather(parent, temp->getRank() + 1, checkRelation(temp->getRank() + 1, "man"),
                                temp->getName());
            }
                // if a fother already exists, override it
            else {
                throw std::invalid_argument("parent already exsist");
            }
        } else { // if the child haven't been found
            throw std::invalid_argument("this child doesnt exists");
        }

    } else { // if the root of the tree doesnt exists
        throw std::invalid_argument("A root doesn't exists");
    }
    return *this;

}


Tree &Tree::addMother(std::string name, std::string parent) {

    if (this->root != nullptr) {
        Node *temp = search(name, this->root, false);
        if (temp != nullptr) { // means the child was found
            if (temp->getMother() == nullptr) {
                temp->setMother(parent, temp->getRank() + 1, checkRelation(temp->getRank() + 1, "woman"),
                                temp->getName());
            }
                // if a mother already exists, override it
            else {
                 throw std::invalid_argument("parent already exsist");
            }
        } else { // if the child haven't been found
            throw std::invalid_argument("this child doesnt exists");
        }

    } else { // if the root of the tree doesnt exists
        throw std::invalid_argument("A root doesn't exists");
    }

    return *this;

}

Node *Tree::search(std::string name, Node *current, bool isRelation) {


    if (current != nullptr) {
        if (!isRelation) {
            if (current->getName() == name) {
                return current;
            }

        } else {
            if (current->getRelation() == name) {
                return current;
            }
        }


        Node *tempF = search(name, current->getFather(), isRelation);
        if (tempF != nullptr) {
            return tempF;
        }
        Node *tempM = search(name, current->getMother(), isRelation);

        if (tempM != nullptr) {
            return tempM;
        }
    }
    return nullptr;
}


void Tree::display() { // a function to display the tree by levels.

    if (this->root == nullptr) // in case its empty
        return;

    std::queue<Node*> q;


    q.push(root);
    while (!q.empty()) { // as long as its not empty

        int numberOfTreeLevel = q.size();
        while (numberOfTreeLevel > 0) {
            Node *top = q.front();
            q.pop();
            std::cout << top->getName() + " ";

            if (top->getFather() != nullptr)
                q.push(top->getFather());
            if (top->getMother() != nullptr)
                q.push(top->getMother());
            numberOfTreeLevel--;

        }
        std::cout << std::endl;

    }


}

std::string Tree::checkRelation(int rank, std::string gender) {


    switch (rank) {
        //if its the child
        case 0:
            return "me";

            //if its father/mother
        case 1:
            if (gender == "man") {
                return "father";
            }
            return "mother";

            // anything above great-great...grandmother of greatfather
            //if its grandfather/grandmother or above
        default:
            std::string ans = "";
            int level = rank - 2;
            for (int i = 0; i < level; i++) {
                ans += "great-";
            }
            if (gender == "man") {
                return ans + "grandfather";
            }
            return ans + "grandmother";

    }

}

std::string Tree::relation(std::string name) {

    Node *temp = search(name, root, false);
    if (temp == nullptr) {
        return "unrelated";
    }
    return temp->getRelation();


}

std::string Tree::find(std::string name) {

    Node *temp = search(name, root, true);
    if (temp == nullptr) {
        throw std::invalid_argument("The tree cannot handle the '" + name + "' relation");
    }
    return temp->getName();


}

void Tree::remove(std::string name) {

    // getting the specific node to delete
    Node *temp = search(name, root, false);


    if (temp != nullptr) {
        // getting the child so after we can point him to null
        Node *child = search(temp->getChildName(), root, false);

        // comparing addresses to know who to delete - mother or father
        if (child->getFather() == temp) {
            child->setFatherNull();
        } else {
            child->setMotherNull();
        }

        deleteTree(temp);


    } 
	else {
    throw std::invalid_argument("The tree doesnt contain " + name);
    }
}
