//
// Created by sivannamma on 4/5/20.
//
#include "doctest.h"
#include "FamilyTree.hpp"

using namespace family;

#include <string>

using namespace std;

TEST_CASE ("find function test") {
    Tree T("sivan"); // sivan is the "root" of the tree (the youngest person).
    T.addMother("sivan", "tamar").addFather("sivan", "igeal").addFather("igeal", "nisim").addMother("igeal",
                                                                                                    "carmela").addFather(
            "tamar", "gamil").addMother("tamar", "shoshana").addMother("shoshana", "naima").addMother("naima",
                                                                                                      "rooth").addFather(
            "rooth", "shavit");
// related family members :
            CHECK((T.find("me") == string("sivan")));
            CHECK((T.find("mother") == string("tamar")));
            CHECK((T.find("father") == string("igeal")));
            CHECK(((T.find("grandfather") == string("gamil"))||(T.find("grandfather") == string("nisim"))));
            CHECK(((T.find("grandmother") == string("carmela"))||(T.find("grandmother") == string("shoshana"))));
            CHECK((T.find("great-grandmother") == string("naima")));
            CHECK((T.find("great-great-grandmother") == string("rooth")));
            CHECK((T.find("great-great-great-grandfather") == string("shavit")));

// unrelated family members :
    try {
        T.find("uncle");
    } catch (const exception &ex) {
                CHECK(ex.what() == string("The tree cannot handle the 'uncle' relation"));
    }

    try {
        T.find("cousin");
    } catch (const exception &ex) {
                CHECK(ex.what() == string("The tree cannot handle the 'cousin' relation"));
    }
    try {
        T.find("great-great-geat-great-grandfather");
    } catch (const exception &ex) {
                CHECK(ex.what() == string("The tree cannot handle the 'great-great-geat-great-grandfather' relation"));
    }
}

TEST_CASE ("add mother-father test") {

    Tree T("shai");
    // father check
            CHECK(T.relation("david") == string("unrelated"));
    T.addFather("shai", "david");
            CHECK(T.relation("david") == string("father"));
            CHECK(T.relation("yossi") == string("unrelated"));
    T.addFather("david", "yossi");
            CHECK(T.relation("david") == string("father"));
            CHECK(T.relation("yossi") == string("grandfather"));
    T.addFather("yossi", "haim");
            CHECK(T.relation("haim") == string("great-grandfather"));


    // mother check
            CHECK(T.relation("rachel") == string("unrelated"));
    T.addMother("shai", "rachel");
            CHECK(T.relation("rachel") == string("mother"));
            CHECK(T.relation("lea") == string("unrelated"));
    T.addMother("rachel", "lea");
            CHECK(T.relation("lea") == string("grandmother"));
            CHECK(T.relation("naama") == string("unrelated"));
    T.addMother("lea", "naama");
            CHECK(T.relation("naama") == string("great-grandmother"));

            CHECK(T.relation("metuka") == string("unrelated"));
    T.addMother("david", "metuka");
            CHECK(T.relation("metuka") == string("grandmother"));
}

TEST_CASE ("replacing test") {

    Tree T("shai");

    // father side check
    T.addFather("shai", "david");
            CHECK(T.relation("david") == string("father"));
    T.addFather("shai", "igeal");
            CHECK(T.relation("igeal") == string("father"));
    T.addFather("igeal", "david");
            CHECK(T.relation("david") == string("grandfather"));
    T.addFather("igeal", "nisim");
            CHECK(T.relation("nisim") == string("grandfather"));
    T.addFather("nisim", "yaakov");
            CHECK(T.relation("yaakov") == string("great-grandfather"));
    T.addFather("nisim", "shlomo");
            CHECK(T.relation("shlomo") == string("great-grandfather"));


    // mother check
    T.addMother("shai", "shoshi");
            CHECK(T.relation("shoshi") == string("mother"));
    T.addMother("shai", "tamar");
            CHECK(T.relation("tamar") == string("mother"));
    T.addMother("tamar", "shoshi");
            CHECK(T.relation("shoshi") == string("grandmother"));
    T.addMother("tamar", "shoshana");
            CHECK(T.relation("shoshana") == string("grandmother"));
    T.addMother("shoshana", "naama");
            CHECK(T.relation("naama") == string("great-grandmother"));
    T.addMother("shoshana", "naima");
            CHECK(T.relation("naima") == string("great-grandmother"));
    T.addMother("naima", "roothy");
            CHECK(T.relation("roothy") == string("great-great-grandmother"));
    T.addMother("naima", "rooth");
            CHECK(T.relation("rooth") == string("great-great-grandmother"));
}

TEST_CASE ("Test relation") {


    family::Tree T("Elad");
    T.addFather("Elad", "Moshe")
            .addMother("Elad", "Vivi")
            .addFather("Moshe", "Amnon")
            .addMother("Moshe", "Atida")
            .addMother("Vivi", "Shoshana")
            .addFather("Vivi", "Aliazer")
            .addMother("Shoshana", "Batia")
            .addFather("Shoshana", "Avner")
            .addMother("Avner", "Rachel")
            .addFather("Batia", "Yakov");


            CHECK(T.relation("Vivi") == string("mother"));
            CHECK(T.relation("Moshe") == string("father"));
            CHECK(T.relation("Atida") == string("grandmother"));
            CHECK(T.relation("Amnon") == string("grandfather"));
            CHECK(T.relation("Shoshana") == string("grandmother"));
            CHECK(T.relation("bozi") == string("unrelated"));
            CHECK(T.relation("Batia") == string("great-grandmother"));
            CHECK(T.relation("Avner") == string("great-grandfather"));
            CHECK(T.relation("Rachel") == string("great-great-grandmother"));
            CHECK(T.relation("Avnerr") == string("unrelated"));
            CHECK(T.relation("Elad") == string("me"));


    family::Tree T2("Omer");
    T2.addFather("Omer", "Dudu")
            .addFather("Dudu", "Gabi")
            .addFather("Gabi", "Shlomo")
            .addFather("Shlomo", "Yakov")
            .addFather("Yakov", "Yosef")
            .addFather("Yosef", "Gili");

            CHECK(T2.relation("Vivi") == string("unrelated"));
            CHECK(T2.relation("Omer") == string("me"));
            CHECK(T2.relation("Dudu") == string("father"));
            CHECK(T2.relation("Gabi") == string("grandfather"));
            CHECK(T2.relation("Shlomo") == string("great-grandfather"));
            CHECK(T2.relation("Yakov") == string("great-great-grandfather"));
            CHECK(T2.relation("Yosef") == string("great-great-great-grandfather"));
            CHECK(T2.relation("Gili") == string("great-great-great-great-grandfather"));
            CHECK(T2.relation("OmEr") == string("unrelated"));
            CHECK(T2.relation("dudu") == string("unrelated"));
            CHECK(T2.relation("GABi") == string("unrelated"));

}


TEST_CASE ("Test remove") {

    Tree T("Elad");
    T.addFather("Elad", "Moshe")
            .addMother("Elad", "Vivi")
            .addFather("Moshe", "Amnon")
            .addMother("Moshe", "Atida")
            .addMother("Vivi", "Shoshana")
            .addFather("Vivi", "Aliazer")
            .addMother("Shoshana", "Batia")
            .addFather("Shoshana", "Avner")
            .addMother("Avner", "Rachel")
            .addFather("Shoshana", "Yakov");

    T.remove("Vivi");

            CHECK(T.relation("Vivi") == string("unrelated"));
            CHECK(T.relation("Aliazer") == string("unrelated"));
            CHECK(T.relation("Shoshana") == string("unrelated"));
            CHECK(T.relation("Batia") == string("unrelated"));
            CHECK(T.relation("Avner") == string("unrelated"));
            CHECK(T.relation("Rachel") == string("unrelated"));
            CHECK(T.relation("Yakov") == string("unrelated"));

    T.remove("Moshe");
            CHECK(T.relation("Atida") == string("unrelated"));
            CHECK(T.relation("Amnon") == string("unrelated"));

    Tree T2("Elad");
    T2.addFather("Elad", "Moshe")
            .addMother("Elad", "Vivi")
            .addFather("Moshe", "Amnon")
            .addMother("Moshe", "Atida")
            .addMother("Vivi", "Shoshana")
            .addFather("Vivi", "Aliazer")
            .addMother("Shoshana", "Batia")
            .addFather("Shoshana", "Avner")
            .addMother("Avner", "Rachel")
            .addFather("Shoshana", "Yakov");


    T2.remove("Shoshana");
            CHECK(T2.relation("Amnon") == string("grandfather"));
    T2.remove("Aliazer");
            CHECK(T2.relation("Aliazer") == string("unrelated"));
            CHECK(T2.find("mother") == string("Vivi"));


    T2.remove("moshe");
            CHECK(T2.relation("Amnon") == string("grandfather"));
            CHECK(((T2.find("grandmother") == string("Atida"))||(T2.find("grandmother") == string("Shoshana"))));

}

TEST_CASE ("Test addFather,addMother -2 ") {

    Tree T("Elad");
            CHECK(T.relation("Yuval") == string("unrelated"));
    T.addFather("Elad", "Yuval");
            CHECK(T.relation("Yuval") == string("father"));
            CHECK(T.find("father") == string("Yuval"));
            CHECK(T.relation("vika") == string("unrelated"));
    T.addMother("Elad", "vika");
            CHECK(T.relation("vika") == string("mother"));
            CHECK(T.relation("Vika") == string("unrelated"));
            CHECK(T.find("mother") == string("vika"));
            CHECK(T.relation("Avi") == string("unrelated"));
    T.addFather("Yuval", "Avi");
            CHECK(T.relation("Avi") == string("grandfather"));
            CHECK(T.relation("Avrom") == string("unrelated"));
    T.addFather("Avi", "Avrom");
            CHECK(T.relation("Avrom") == string("great-grandfather"));
            CHECK(T.find("great-grandfather") == string("Avrom"));

}


TEST_CASE ("Test remove2") {

    Tree T("sivan"); // sivan is the "root" of the tree (the youngest person).
    T.addMother("sivan", "tamar")
    .addFather("sivan", "igeal")
    .addFather("igeal", "nisim")
    .addMother("igeal","carmela")
    .addFather("tamar", "gamil")
    .addMother("tamar", "shoshana")
    .addMother("shoshana", "naima")
    .addMother("naima","rooth")
    .addFather("rooth", "shavit");

            CHECK(T.relation("rooth") == string("great-great-grandmother"));
            CHECK(T.relation("shavit") == string("great-great-great-grandfather"));
    T.remove("rooth"); // after deleting, both should not be in the reww
            CHECK(T.relation("rooth") == string("unrelated"));
            CHECK(T.relation("shavit") == string("unrelated"));

            CHECK(T.relation("igeal") == string("father"));
            CHECK(T.relation("nisim") == string("grandfather"));
            CHECK(T.relation("carmela") == string("grandmother"));

    T.remove("igeal");
            CHECK(T.relation("igeal") == string("unrelated"));
            CHECK(T.relation("nissim") == string("unrelated"));
            CHECK(T.relation("carmela") == string("unrelated"));

            CHECK(T.relation("tamar") == string("mother"));
            CHECK(T.relation("shoshana") == string("grandmother"));
    T.remove("tamar");
            CHECK(T.relation("tamar") == string("unrelated"));
            CHECK(T.relation("shoshana") == string("unrelated"));

}

