#ifndef MATALA2_ANCESTORTREE_H
#define MATALA2_ANCESTORTREE_H

#include "string"
#include "queue"
#include <stdexcept>
#include <iostream>

namespace family {
    class Node {
    private:

        std::string name;
        int rank;
        std::string relation;
        std::string childName;
        Node *father;
        Node *mother;



    public:


        // outline functions
        Node(std::string name, int rank, std::string relation, std::string childName);

        // return a pointer to the father
        Node *getFather();
        // returns a pointer to the mother
        Node *getMother();
        // set the current pointer to father null
        void setFatherNull();
        // set the current pointer to mother null
        void setMotherNull();
        // setting new father
        void setFather(std::string name, int rank, std::string relation, std::string childName);
        // setting new mother
        void setMother(std::string name, int rank, std::string relation, std::string childName);
        // setting name
        void setName(std::string name);

        // returns the rank of the node(the depth)
        int &getRank();

        // returns the name of the person in this node
        std::string getName();

        // get the gender of the preson
        std::string getRelation();
        // getting the child name
        std::string getChildName();

    };


    class Tree {
    private:
        Node *root;

    public:
        //constructor
        Tree(std::string root);


        //destructor
        ~Tree();

        Tree &addFather(std::string name, std::string parent);

        Tree &addMother(std::string name, std::string parent);

        // given a name the function returns the relation of the person in the tree
        std::string relation(std::string name);

        // the reverse function of relation - given a relation string and reutnrs the name of this person represents this relation
        std::string find(std::string name);

        // search the given node by name/relation in the tree - returns its pointer
        // the bool isRelation - detemnies what to look for in the tree name/relation
        Node *search(std::string name, Node *current, bool isRelation);

        // display the tree
        void display();

        // remove a node
        void remove(std::string name);

        // function to delete all nodes in the tree
        void deleteTree(Node *root);

        // this function returns the relation of the current node
        std::string checkRelation(int rank, std::string gender);


    };

}
#endif //MATALA2_ANCESTORTREE_H
