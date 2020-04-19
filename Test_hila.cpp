#include "doctest.h"
#include "FamilyTree.hpp"

using namespace family;

#include <string>
using namespace std;

TEST_CASE("Test 1 addFather & addMother & relation") {

    Tree T ("Shalom");
    T.addFather("Shalom", "Aharon").addMother("Shalom", "Yafa");

    CHECK(T.relation("Shalom") == string("me"));
    CHECK(T.relation("Aharon") == string("father"));
    CHECK(T.relation("Yafa") == string("mother"));

    CHECK_THROWS(T.addFather("Shalom", "Yosef")); //Shalom already has a father
    CHECK_THROWS(T.addMother("Shalom", "Meri"));

    T.addMother("Yafa", "Ahuva").addMother("Ahuva", "Miriam");

    CHECK(T.relation("Ahuva") == string("grandmother"));
    CHECK(T.relation("Miriam") == string("great-grandmother"));
    CHECK_THROWS(T.addMother("Yafa", "Michal"));
    CHECK_THROWS(T.addMother("Ahuva", "Michal"));
    CHECK_THROWS(T.addFather("Sason", "Yaakov")); //Sason is not on the tree

    T.addFather("Yafa", "Avi").addFather("Aharon", "Yigal").addMother("Aharon", "Nira");

    CHECK(T.relation("Avi") == string("grandfather"));
    CHECK(T.relation("Yigal") == string("grandfather"));
    CHECK(T.relation("Nira") == string("grandmother"));
    CHECK_THROWS(T.addFather("Yafa", "Yishai"));
    CHECK_THROWS(T.addMother("Aharon", "Tzila"));

    //check case of searching name that doesn't exist on the tree 
    CHECK(T.relation("Hila") == string("unrelated"));
    CHECK(T.relation("Ben") == string("unrelated"));
    CHECK(T.relation("Eva") == string("unrelated"));
    CHECK(T.relation("Shimon") == string("unrelated"));
    CHECK(T.relation("Yossi") == string("unrelated"));
}

TEST_CASE("Test 1 find") {

    Tree T ("Yonit");
    T.addFather("Yonit", "Arel").addMother("Yonit", "Ronit")
     .addFather("Ronit", "Yonatan").addMother("Ronit", "Simha")
     .addFather("Arel", "Yosef").addMother("Arel", "Dikla");

    CHECK(T.find("mother") == string("Ronit"));
    CHECK(T.find("father") == string("Arel"));
    CHECK((T.find("grandfather") == string("Yosef") || T.find("grandfather") == string("Yonatan")));
    CHECK((T.find("grandmother") == string("Simha") || T.find("grandmother") == string("Dikla")));
    //CHECK_THROWS(T.find("uncle")); //there is no option of "uncle" on this tree
    //CHECK_THROWS(T.find("sister"));
    CHECK_THROWS(T.find("great-grandfather")); //there is no great-grandfather here
    CHECK_THROWS(T.find("great-grandmother"));
    
    T.addMother("Yosef", "Efrat").addFather("Yosef", "Shmuel").addFather("Shmuel", "Israel");

    CHECK(T.find("great-grandmother") == string("Efrat"));
    CHECK(T.find("great-grandfather") == string("Shmuel"));
    CHECK(T.find("great-great-grandfather") == string("Israel"));
    CHECK_THROWS(T.find("great-great-grandmother"));

    T.addFather("Yonatan", "Ofer").addMother("Yonatan", "Sima").addMother("Simha", "Ester"); 

    CHECK((T.find("great-grandfather") == string("Shmuel") || T.find("great-grandfather") == string("Ofer"))); 
    CHECK((T.find("great-grandmother") == string("Efrat") 
        || T.find("great-grandmother") == string("Sima")
        || T.find("great-grandmother") == string("Ester"))); 
    CHECK_THROWS(T.find("great-great-great-grandfather"));
    CHECK_THROWS(T.find("great-great-great-great-grandfather"));
}

TEST_CASE("Test 1 remove") {

    Tree T ("Maya");
    T.addMother("Maya", "Anat").addFather("Maya", "Rami")
     .addMother("Anat", "Rivka").addFather("Anat", "Yoni")
     .addMother("Yoni", "Vered").addFather("Yoni", "Shlomi")
     .addFather("Rami", "David");

    //CHECK_THROWS(T.remove("Maya")); //try to remove the root --> exception

    CHECK((T.find("grandfather") == string("David") || T.find("grandfather") == string("Yoni")));

    CHECK(T.find("father") == string("Rami"));
    T.remove("Rami"); 
    CHECK_THROWS(T.find("father")); // removed the father
    CHECK(T.find("grandfather") == string("Yoni")); //because David has removed from the tree while removing Rami

    CHECK(T.find("great-grandmother") == string("Vered")); 
    CHECK(T.find("great-grandfather") == string("Shlomi")); 
    T.remove("Vered");
    CHECK_THROWS(T.find("great-grandmother"));
    T.remove("Yoni");
    CHECK_THROWS(T.find("great-grandfather"));
    CHECK_THROWS(T.find(T.find("grandfather")));

    T.addFather("Anat", "Nir"); //we've removed Yoni, sowe can add new father to Anat now
    CHECK(T.find("grandfather") == string("Nir")); 
    CHECK(T.find("grandmother") == string("Rivka"));
    T.remove("Rivka"); 
    CHECK_THROWS(T.find("grandmother")); 
    T.remove("Anat"); 
    CHECK_THROWS(T.find("grandfather")); 
    CHECK_THROWS(T.find("mother"));
}

TEST_CASE("Test 2 addFather & addMother & relation"){

    Tree T ("Ronny");
    T.addFather("Ronny", "Dan").addMother("Ronny", "Rivka");

    CHECK(T.relation("Ronny") == string("me"));
    CHECK(T.relation("Dan") == string("father"));
    CHECK(T.relation("Rivka") == string("mother"));
    CHECK(T.relation("Rina") == string("unrelated"));
    CHECK(T.relation("Noa") == string("unrelated"));
    CHECK_THROWS(T.addFather("Ronny", "Liad")); // already has a father
    CHECK_THROWS(T.addMother("Ronny", "Lital"));
    
    T.addMother("Rivka", "Arbel").addMother("Arbel", "Rita").addFather("Dan", "Ronen").addFather("Ronen", "Almog");

    CHECK(T.relation("Arbel") == string("grandmother"));
    CHECK(T.relation("Rita") == string("great-grandmother"));
    CHECK(T.relation("Ronen") == string("grandfather"));
    CHECK(T.relation("Almog") == string("great-grandfather"));

    CHECK_THROWS(T.addMother("Ronny", "Michal")); // already has a mother
    CHECK_THROWS(T.addMother("Arbel", "Dana"));

    CHECK_THROWS(T.addFather("Gonen", "a")); // not on the tree
    CHECK_THROWS(T.addFather("Gina", "b")); 

    T.addFather("Arbel", "Avi").addFather("Almog", "Yigal").addMother("Dan", "Hadar");

    CHECK(T.relation("Avi") == string("great-grandfather"));
    CHECK(T.relation("Yigal") == string("great-great-grandfather"));
    CHECK(T.relation("Hadar") == string("grandmother"));

    CHECK_THROWS(T.addFather("Arbel", "Yishai")); // already has father
    CHECK_THROWS(T.addMother("Dan", "Gal"));

    CHECK_THROWS(T.addMother("Teva", "a")); // not in tree
    CHECK_THROWS(T.addMother("Toly", "b")); 
    CHECK_THROWS(T.addMother("Yonatan", "c"));
    CHECK_THROWS(T.addMother("Aaron", "d"));
    CHECK_THROWS(T.addMother("Norit", "e")); 

}

TEST_CASE("Test 2 find"){

    Tree T ("Shimrit");
    T.addFather("Shimrit", "Shlomi").addMother("Shimrit", "Shani")
     .addFather("Shlomi", "Yona").addMother("Shlomi", "Shira")
     .addFather("Shani", "Snir").addMother("Shani", "Shayli");

    CHECK(T.find("mother") == string("Shani"));
    CHECK(T.find("father") == string("Shlomi"));
    CHECK((T.find("grandfather") == string("Yona") || T.find("grandfather") == string("Snir")));
    CHECK((T.find("grandmother") == string("Shira") || T.find("grandmother") == string("Shayli")));
    //CHECK_THROWS(T.find("brother")); //there is no option of "brother" on this tree
    CHECK_THROWS(T.find("friend"));
    CHECK_THROWS(T.find("great-grandfather")); //there is no great-grandfather here
    CHECK_THROWS(T.find("great-grandmother"));
    
    T.addMother("Snir", "ShemTov").addFather("Snir", "Hanoh").addFather("Hanoh", "Alex");

    CHECK(T.find("great-grandfather") == string("Hanoh"));
    CHECK(T.find("great-grandmother") == string("ShemTov"));
    CHECK(T.find("great-great-grandfather") == string("Alex"));
    
    CHECK_THROWS(T.find("great-great-great-grandmother")); //there is no great-great-great-grandmother 
}

TEST_CASE("Test 2 remove"){
    Tree T ("Omri");
    T.addMother("Omri", "Hanna").addFather("Omri", "Omer")
     .addMother("Hanna", "Rachel").addFather("Hanna", "Loren")
     .addMother("Loren", "Calanit").addFather("Loren", "Moky")
     .addFather("Omer", "Nadav");

    CHECK_THROWS(T.remove("Omri")); //try to remove the root --> exception

    CHECK((T.find("grandfather") == string("Nadav") || T.find("grandfather") == string("Loren")));

    CHECK(T.find("father") == string("Omer"));
    T.remove("Omer"); 
    CHECK_THROWS(T.find("father"));
    CHECK(T.find("grandfather") == string("Loren")); // Nadav has removed from the tree while removing Omer

    CHECK(T.find("great-grandmother") == string("Calanit")); 
    CHECK(T.find("great-grandfather") == string("Moky")); 
    T.remove("Calanit");
    CHECK_THROWS(T.find("great-grandmother"));
    T.remove("Loren");
    CHECK_THROWS(T.find("great-grandfather"));
    CHECK_THROWS(T.find(T.find("grandfather")));

    T.addFather("Hanna", "Nissan"); //removed Loren, sowe can add new father to Hanna now
    CHECK(T.find("grandfather") == string("Nissan")); 
    CHECK(T.find("grandmother") == string("Rachel"));
}
