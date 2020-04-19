/**
 * A demonstration test program for Gimatriya calculation.
 * 
 * Use this as a basis to build a more complete Test.cpp file.
 * 
 * Date: 2020-02
 */

#include "doctest.h"
#include "FamilyTree.hpp"

#include <string>
using namespace std;

TEST_CASE("Test case 1") {  
	family::Tree T ("Yosef"); // Yosef is the "root" of the tree (the youngest person).
	T.addFather("Yosef", "Yaakov");   // Tells the tree that the father of Yosef is Yaakov.
	T.addMother("Yosef", "Rachel");
	T.addFather("Yaakov", "Isaac");
	T.addMother("Yaakov", "Rivka");
	T.addFather("Isaac", "Avraham");
	T.addFather("Avraham", "Terah");

    CHECK(T.relation("Rivka") == string("mother"));
    CHECK(T.relation("Terah") == string("great-great-grandfather"));
    CHECK(T.relation("xyz") == string("unrelated"));

    CHECK(T.find("mother") == string("Rivka"));
    CHECK(T.find("great-great-grandfather") == string("Terah"));

    /* Add more tests here */
}
