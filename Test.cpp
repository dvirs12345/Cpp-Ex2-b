/**
 * unit test to FamilyTree
 * AUTHORs: RoiPeleg and TalAbed
 * */
#include "doctest.h"
#include "FamilyTree.hpp"
using namespace family;
#include <string>

// a macro to simply check exception b must be init to FALSE!
#define checkExp(T, f, b)     \
    {                         \
        try                   \
        {                     \
            T.f;              \
        }                     \
        catch (exception & e) \
        {                     \
            b = true;         \
        }                     \
    }
#define initTree(T)                        \
    {                                      \
        T.addFather("Yosef", "Yaakov")     \
            .addMother("Yosef", "Rachel")  \
            .addFather("Yaakov", "Isaac")  \
            .addMother("Yaakov", "Rivka")  \
            .addFather("Isaac", "Avraham") \
            .addFather("Avraham", "Terah") \
            .addMother("Rivka", "m")       \
            .addMother("m", "m1");         \
    }
using namespace std;
Tree T("Yosef");
Tree T2("Noa");
TEST_CASE("Test add")
{
    T.addFather("Yosef", "Yaakov")
        .addMother("Yosef", "Rachel")
        .addFather("Yaakov", "Isaac")
        .addMother("Yaakov", "Rivka")
        .addFather("Isaac", "Avraham")
        .addFather("Avraham", "Terah")
        .addMother("Rivka", "m")
        .addMother("m", "m1");
    CHECK(T.find("father") == "Yaakov");
    CHECK(T.find("mother") == "Rachel");
    CHECK(T.find("grandfather") == "Issac");
    CHECK(T.find("grandmother") == "Rivka");
    CHECK(T.find("great-grandfather") == "Avraham");
    CHECK(T.find("great-great-grandfather") == "Terah");
    CHECK(T.find("great-grandmother") == "m");
    CHECK(T.find("great-great-grandmother") == "m1");
    bool b = false;
    checkExp(T, addFather("Yaakov", "ff"), b)
        CHECK(b == true);
    b = false;
    checkExp(T, addMother("Yaakov", "r2"), b)
        CHECK(b == true);
    b = false;
    checkExp(T, addMother("Rivka", "r2"), b)
        CHECK(b == true);
    b = false;
    checkExp(T, addMother("m", "r2"), b)
        CHECK(b == true);
}
TEST_CASE("Test remove")
{
    T.remove("m1");
    CHECK(T.relation("m1") == "unrealted");
    T.remove("Rivka");
    CHECK(T.relation("m") == "unrealted");
    CHECK(T.relation("Rivka") == "unrealted");
    T.remove("Yaakov");
    CHECK(T.relation("Issac") == "unrealted");
    CHECK(T.relation("Terah") == "unrealted");
    CHECK(T.relation("Avraham") == "unrealted");
    bool b = false;
    checkExp(T, remove("Yosef"), b)
        CHECK(b == true);
        b = false;
    checkExp(T, remove("Yaakov"), b)
        CHECK(b == true);
        b = false;
    checkExp(T, remove("m1"), b)
        CHECK(b == true);
        b = false;
    checkExp(T, remove("Issac"), b)
        CHECK(b == true);
        b = false;
    checkExp(T, remove("yossi"), b)
        CHECK(b == true);
}
TEST_CASE("Test realtion")
{
    T2.addFather("Noa", "Shai")
        .addMother("Noa", "Shani")
        .addFather("Shai", "Pinchas")
        .addMother("Shai", "Riki")
        .addFather("Shani", "Silvan")
        .addMother("Shani", "Rachel")
        .addFather("Pinchas", "Avraham")
        .addMother("Pinchas", "Sara")
        .addFather("Riki", "Yakov")
        .addMother("Riki", "Lea")
        .addFather("Silvan", "Meni")
        .addMother("Silvan", "Hadas")
        .addFather("Rachel", "Almog")
        .addMother("Rachel", "Ariel")
        .addFather("Avraham", "Yosef")
        .addMother("Avraham", "Shontal")
        .addFather("Shontal", "Haim")
        .addMother("Shontal", "Sheli");

    CHECK(T2.find("Shai")=="father");
    CHECK(T2.find("Shani")=="mother");
    CHECK(T2.find("Pinchas")=="grandfather");
    CHECK(T2.find("Silvan")=="grandfather");
    CHECK(T2.find("Riki")=="grandmother");
    CHECK(T2.find("Rachel")=="grandmother");
    CHECK(T2.find("Avraham")=="great-grandfather");
    CHECK(T2.find("Meni")=="great-grandfather");
    CHECK(T2.find("Yakov")=="great-grandfather");
    CHECK(T2.find("Almog")=="great-grandfather");
    CHECK(T2.find("Sara")=="great-grandmother");
    CHECK(T2.find("Lea")=="great-grandmother");
    CHECK(T2.find("Hadas")=="great-grandmother");
    CHECK(T2.find("Ariel")=="great-grandmother");
    CHECK(T2.find("Yosef")=="great-great-grandfather");
    CHECK(T2.find("Shontal")=="great-great-grandmother");
    CHECK(T2.find("Haim")=="great-great-great-grandfather");
    CHECK(T2.find("Sheli")=="great-great-great-grandmother");
    CHECK(T2.find("Beni")=="unrelated");

    CHECK(T2.find("Pinchas")=="father");
    CHECK(T2.find("Rachel")=="mother");
    CHECK(T2.find("Avraham")=="grandfather");
    CHECK(T2.find("Meni")=="grandfather");
    CHECK(T2.find("Lea")=="grandmother");
    CHECK(T2.find("Ariel")=="grandmother");
    CHECK(T2.find("Yosef")=="great-grandfather");
    CHECK(T2.find("Silvan")=="great-grandfather");
    CHECK(T2.find("Shai")=="great-grandfather");
    CHECK(T2.find("Dvir")=="great-grandfather");
    CHECK(T2.find("Riki")=="great-grandmother");
    CHECK(T2.find("Rivka")=="great-grandmother");
    CHECK(T2.find("Shontal")=="great-grandmother");
    CHECK(T2.find("Shani")=="great-grandmother");
    CHECK(T2.find("Haim")=="great-great-grandfather");
    CHECK(T2.find("Noa")=="great-great-grandmother");
    CHECK(T2.find("Beni")=="great-great-great-grandfather");
    CHECK(T2.find("Hadas")=="great-great-great-grandmother");
    CHECK(T2.find("Shani")=="unrelated");
}
TEST_CASE("Test find")
{   
    CHECK(T2.find("father")=="Shai");
    CHECK(T2.find("mother")=="Shani");
    CHECK(T2.find("grandfather")=="Pinchas");
    CHECK(T2.find("grandfather")=="Silvan");
    CHECK(T2.find("grandmother")=="Riki");
    CHECK(T2.find("grandmother")=="Rachel");
    CHECK(T2.find("great-grandfather")=="Avraham");
    CHECK(T2.find("great-grandfather")=="Meni");
    CHECK(T2.find("great-grandfather")=="Yakov");
    CHECK(T2.find("great-grandfather")=="Almog");
    CHECK(T2.find("great-grandmother")=="Sara");
    CHECK(T2.find("great-grandmother")=="Lea");
    CHECK(T2.find("great-grandmother")=="Hadas");
    CHECK(T2.find("great-grandmother")=="Ariel");
    CHECK(T2.find("great-great-grandfather")=="Yosef");
    CHECK(T2.find("great-great-grandmother")=="Shontal");
    CHECK(T2.find("great-great-great-grandfather")=="Haim");
    CHECK(T2.find("great-great-great-grandmother")=="Sheli");

    CHECK(T2.find("father")=="Pinchas");
    CHECK(T2.find("mother")=="Rachel");
    CHECK(T2.find("grandfather")=="Avraham");
    CHECK(T2.find("grandfather")=="Meni");
    CHECK(T2.find("grandmother")=="Lea");
    CHECK(T2.find("grandmother")=="Ariel");
    CHECK(T2.find("great-grandfather")=="Yosef");
    CHECK(T2.find("great-grandfather")=="Silvan");
    CHECK(T2.find("great-grandfather")=="Shai");
    CHECK(T2.find("great-grandfather")=="Dvir");
    CHECK(T2.find("great-grandmother")=="Riki");
    CHECK(T2.find("great-grandmother")=="Rivka");
    CHECK(T2.find("great-grandmother")=="Shontal");
    CHECK(T2.find("great-grandmother")=="Shani");
    CHECK(T2.find("great-great-grandfather")=="Haim");
    CHECK(T2.find("great-great-grandmother")=="Noa");
    CHECK(T2.find("great-great-great-grandfather")=="Beni");
    CHECK(T2.find("great-great-great-grandmother")=="Hadas");

    CHECK(T2.find("father")=="Oded");
    CHECK(T2.find("father")=="Ilan");
    CHECK(T2.find("father")=="Kobi");
    CHECK(T2.find("father")=="Natan");
    CHECK(T2.find("father")=="Geri");

    bool b = false;
    checkExp(T2, find("great-great-great-great-grandmother"), b)
        CHECK(b == true);
    b = false;
    checkExp(T2, find("great-great-great-great-grandfather"), b)
        CHECK(b == true);
    b = false;
    checkExp(T2, find("great-grandfather"), b)
        CHECK(b==true);
}