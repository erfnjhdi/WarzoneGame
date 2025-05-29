// #include "playerDriver.h"
//
// void playerTester()
// {
//     cout << "\n----Generating Player----" <<endl;
//     Player p("Joon");
//
//     cout << "\n----Adding Territory to Player----" <<endl;
//     p.addTerritory("Canada");
//     p.addTerritory("USA");
//     p.addTerritory("Mexico");
//     p.addTerritory("UK");
//
//     cout << "\n----Printing Player Info----" <<endl;
//     cout << p;
//
//     cout << "----Printing Defense Info----" <<endl;
//     p.toDefend();
//     p.toDefend();
//     cout << endl;
//
//     cout << "----Printing Attack Info----" <<endl;
//     p.toAttack();
//     p.toAttack();
//     cout << endl;
//
//
//     cout << "\n----Removing Territory from Player----" <<endl;
//     p.removeTerritory("USA");
//     p.removeTerritory("Mexico");
//
//     cout << "\n----Printing Player Info----" <<endl;
//     cout << p;
//
//     cout << "\n----Printing Attack Info----" <<endl;
//     p.toAttack();
//     p.toAttack();
//
//     cout << " " << endl;
//     cout << "\n----Issuing Order------" << endl;
//     p.issueOrder("attack Canada");
//     p.issueOrder("defend USA");
//
//     cout << "\n----Printing Player Info----" <<endl;
//     cout << p;
//
//     cout << "\n----Testing Copy Constructor----" <<endl;
//     Player p2(p);
//     cout << p2;
//
//     cout << "\n----Testing Assignment Operator----" <<endl;
//     Player p3 = p;
//     cout << p3;
//     p3.issueOrder("defend USA");
//     cout << p3;
//
// }