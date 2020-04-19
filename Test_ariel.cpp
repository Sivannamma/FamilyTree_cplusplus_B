 
#include "doctest.h"
#include "FamilyTree.hpp"

#include <string>
using namespace std;

TEST_CASE("Reference add Tree case") { 
	family::Tree T ("Yosef");
	T.addFather("Yosef", "Yaakov")
	 .addMother("Yosef", "Rachel")
	 .addFather("Yaakov", "Isaac")
	 .addMother("Yaakov", "Rivka")
	 .addFather("Isaac", "Avraham")
	 .addFather("Avraham", "Terah");
}

TEST_CASE("Yosef Tree case") {  
	// Add test case
	family::Tree T ("Yosef");
	T.addFather("Yosef", "Yaakov");
	T.addMother("Yosef", "Rachel");
	CHECK_THROWS(T.addFather("Yosef", "Yaakov")); // duplicate father
	CHECK_THROWS(T.addMother("Yosef", "Rivka"));  // duplicate mother
	T.addFather("Yaakov", "Isaac");
	T.addMother("Yaakov", "Rivka");
	T.addFather("Rachel", "Avi");
	T.addMother("Rachel", "Ruti");
	T.addFather("Isaac", "Avraham");
	T.addMother("Isaac", "Ruti");
	CHECK_THROWS(T.addFather("Isaac", "Israel"));  // duplicate father
	CHECK_THROWS(T.addMother("Isaac", "Ruti"));    // duplicate mother
	T.addFather("Avraham", "Yosi");
	T.addMother("Avraham", "Shelly");
	T.addFather("Avi", "Israel");
	T.addMother("Avi", "Sara");
	CHECK_THROWS(T.addFather("Avraham", "Avraham"));    // duplicate father
	CHECK_THROWS(T.addMother("Avraham", "Sara"));       // duplicate mother
	 
	// Relation test case
	CHECK(T.relation("Yaakov") == string("father"));
	CHECK(T.relation("Rachel") == string("mother"));
	CHECK(T.relation("Isaac") == string("grandfather"));
	CHECK(T.relation("Rivka") == string("grandmother"));
	CHECK(T.relation("Avi") == string("grandfather"));
	CHECK((T.relation("Ruti") == string("grandmother") || T.relation("Ruti") == string("great-grandmother")));
	CHECK(T.relation("Avraham") == string("great-grandfather"));
	CHECK((T.relation("Ruti") == string("grandmother") || T.relation("Ruti") == string("great-grandmother")));
	CHECK(T.relation("Israel") == string("great-grandfather"));
	CHECK(T.relation("Sara") == string("great-grandmother"));
	CHECK(T.relation("Yosi") == string("great-great-grandfather"));
    CHECK(T.relation("Shelly") == string("great-great-grandmother"));

    CHECK(T.relation("xyz") == string("unrelated"));
	CHECK(T.relation("Omer") == string("unrelated"));
	CHECK(T.relation("Ariel") == string("unrelated"));
	CHECK(T.relation(" ") == string("unrelated"));
	CHECK(T.relation("  Ariel") == string("unrelated"));

	// Find test case
	CHECK(T.find("father") == string("Yaakov"));
	CHECK(T.find("mother") == string("Rachel"));
	CHECK((T.find("grandfather") == string("Isaac") || T.find("grandfather") == string("Avi")));
	CHECK((T.find("grandmother") == string("Rivka") || T.find("grandmother") == string("Ruti")));
	CHECK((T.find("great-grandmother") == string("Sara") || T.find("great-grandmother") == string("Ruti")));
	CHECK((T.find("great-grandfather") == string("Avraham") || T.find("great-grandfather") == string("Israel")));
	CHECK(T.find("great-great-grandfather") == string("Yosi"));
	CHECK(T.find("great-great-grandmother") == string("Shelly"));

	CHECK_THROWS(T.find("grandfatrher"));
	CHECK_THROWS(T.find("great"));
	CHECK_THROWS(T.find(" "));
	CHECK_THROWS(T.find("   great"));
	CHECK_THROWS(T.find("grandfatrher   "));
	CHECK_THROWS(T.find("great,great,grandmother"));
	CHECK_THROWS(T.find("great?grandmother"));
	CHECK_THROWS(T.find("great grandmother"));

	// Remove test case
	//CHECK_THROWS(T.remove("Yosef"));  // removing the root is an error
	CHECK_THROWS(T.remove(" "));      // removing a non-existent person
	CHECK_THROWS(T.remove("xyz"));
	CHECK_THROWS(T.remove("Ariel"));
	CHECK_THROWS(T.remove("  Rivka"));

	T.remove("Yosi");  // remove the great-great-grandfather
	CHECK_THROWS(T.find("great-great-grandfather"));  // A removed relation does not exist
	T.addFather("Avraham", "Ido");  // Add a new father after removal
	T.remove("Avi");
	CHECK_THROWS(T.addFather("Avi", "Israel"));  // add to a removed person
	T.addFather("Rachel", "Shmual");
	T.remove("Isaac");
	T.remove("Rivka");
	T.remove("Ruti");
	CHECK_THROWS(T.find("grandmother"));
	CHECK_THROWS(T.addFather("Isaac", "Avraham"));
	CHECK_THROWS(T.addMother("Isaac", "Ruti"));
	CHECK_THROWS(T.addFather("Rivka", "Israel"));
	CHECK_THROWS(T.addMother("Rivka", "Sara"));
	T.remove("Yaakov");  // remove father
	T.remove("Rachel");  // remove mother
	CHECK_THROWS(T.find("father"));
	CHECK_THROWS(T.find("mother"));
	CHECK_THROWS(T.addFather("Yaakov", "Avraham"));   // add to non-existent person
	CHECK_THROWS(T.addMother("Yaakov", "Ruti"));      // add to non-existent person
	CHECK_THROWS(T.addFather("Rachel", "Avraham"));   // add to non-existent person
	CHECK_THROWS(T.addMother("Rachel", "Ruti"));      // add to non-existent person
}

/*
TEST_CASE("Strange string Tree case") {  
	// Add test case
	family::Tree T ("OliVeR$");
	T.addFather("OliVeR$", "fEliXX");
	T.addMother("OliVeR$", "#miA");
	CHECK_THROWS(T.addFather("OliVeR$", "Yaa kov"));
	CHECK_THROWS(T.addMother("OliVeR$", "Rivka"));
	T.addFather("fEliXX", "eLi9");
	T.addMother("fEliXX", "IRis-");
	T.addFather("#miA", "osC7ar");
	T.addMother("#miA", "AvA");
	T.addFather("IRis-", "le0");
	T.addMother("IRis-", "aB3igaIl");
	CHECK_THROWS(T.addFather("IRis-", "Israel"));
	CHECK_THROWS(T.addMother("IRis-", "Ruti"));
	 
	// Relation test case
	CHECK(T.relation("fEliXX") == string("father"));
	CHECK(T.relation("#miA") == string("mother"));
	CHECK(T.relation("eLi9") == string("grandfather"));
	CHECK(T.relation("IRis-") == string("grandmother"));
	CHECK(T.relation("osC7ar") == string("grandfather"));
	CHECK(T.relation("AvA") == string("grandmother"));
	CHECK(T.relation("le0") == string("great-grandfather"));
	CHECK(T.relation("aB3igaIl") == string("great-grandmother"));

    CHECK(T.relation("fEli XX") == string("unrelated"));
	CHECK(T.relation("&miA") == string("unrelated"));
	CHECK(T.relation("leo") == string("unrelated"));
	CHECK(T.relation(" ") == string("unrelated"));
	CHECK(T.relation("  osC7ar") == string("unrelated"));

	// Find test case
	CHECK(T.find("father") == string("fEliXX"));
	CHECK(T.find("mother") == string("#miA"));
	CHECK((T.find("grandfather") == string("eLi9") || T.find("grandfather") == string("osC7ar")));
	CHECK((T.find("grandmother") == string("IRis-") || T.find("grandmother") == string("AvA")));
	CHECK(T.find("great-grandfather") == string("le0"));
	CHECK(T.find("great-grandmother") == string("aB3igaIl"));

	CHECK_THROWS(T.find("grandfatrher"));
	CHECK_THROWS(T.find("great"));
	CHECK_THROWS(T.find(" "));
	CHECK_THROWS(T.find("   great"));
	CHECK_THROWS(T.find("grandfatrher   "));
	CHECK_THROWS(T.find("great,great,grandmother"));
	CHECK_THROWS(T.find("great?grandmother"));
	CHECK_THROWS(T.find("great grandmother"));

	// Remove test case
	CHECK_THROWS(T.remove("OliVeR$"));

	T.remove("aB3igaIl");
	CHECK_THROWS(T.find("great-grandmother"));
	T.addMother("IRis-", "aB3igaIl");
	T.remove("fEliXX");
	CHECK_THROWS(T.addFather("eLi9", "Israel"));
	CHECK_THROWS(T.addMother("eLi9", "Ruti"));
	CHECK_THROWS(T.find("great-grandfather"));
	T.addFather("OliVeR$", "fEliXX");
	T.remove("osC7ar");
	CHECK_THROWS(T.find("grandfather"));
	T.remove("#miA");
	CHECK_THROWS(T.addFather("#miA", "Avraham"));
	CHECK_THROWS(T.addMother("#miA", "Ruti"));
	T.remove("fEliXX");
	CHECK_THROWS(T.find("father"));
	CHECK_THROWS(T.find("mother"));
}

TEST_CASE("Empty string Tree case") {  
	// Add test case
	family::Tree T (" ");
	T.addFather(" ", "  ");
	T.addMother(" ", "   ");
	CHECK_THROWS(T.addFather(" ", "Yakov"));
	CHECK_THROWS(T.addMother(" ", "     "));
	T.addFather("  ", "    ");
	T.addMother("  ", "     ");
	CHECK_THROWS(T.addFather("  ", "         "));
	CHECK_THROWS(T.addMother("  ", "Rut  i"));

	// Relation test case
	CHECK(T.relation("  ") == string("father"));
	CHECK(T.relation("   ") == string("mother"));
	CHECK(T.relation("    ") == string("grandfather"));
	CHECK(T.relation("     ") == string("grandmother"));

    CHECK(T.relation("fli XX") == string("unrelated"));
	CHECK(T.relation("leo") == string("unrelated"));
	CHECK(T.relation("  osC7ar") == string("unrelated"));

	// Find test case
	CHECK(T.find("father") == string("  "));
	CHECK(T.find("mother") == string("   "));
	CHECK(T.find("grandfather") == string("    "));
	CHECK(T.find("grandmother") == string("     "));

	CHECK_THROWS(T.find("  "));
	CHECK_THROWS(T.find("great"));
	CHECK_THROWS(T.find("   great"));

	// Remove test case
	CHECK_THROWS(T.remove(" "));

	T.remove("     ");
	CHECK_THROWS(T.find("grandmother"));
	T.remove("  ");
	CHECK_THROWS(T.addFather("  ", "     "););
	CHECK_THROWS(T.addMother("  ", "  Ru ti"););
	CHECK_THROWS(T.find("father"));
	T.remove("   ");
	CHECK_THROWS(T.find("mother"));
	CHECK_THROWS(T.addFather("   ", "        "););
	CHECK_THROWS(T.addMother("   ", "Rut   i "););
}
*/