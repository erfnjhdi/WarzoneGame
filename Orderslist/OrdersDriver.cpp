/*
#include "../Orderslist/Orders.h"
#include "../Player/Player.h"
#include "../Map/Map.h"
#include "../LoggingObserver/LoggingObserver.h"
#include <iostream>

void testOrderExecution() {
    std::cout << "\n========== Testing Order Execution ==========\n";
    
    // Get logger instance and set up test objects
    LogObserver* logger = LogObserver::getInstance();
    
    // Create test territories
    Player_Territory* t1 = new Player_Territory(1, "Territory1");
    Player_Territory* t2 = new Player_Territory(2, "Territory2");
    Player_Territory* t3 = new Player_Territory(3, "Territory3");
    
    // Set up adjacent territories
    t1->addAdjacentTerritory(t2);
    t2->addAdjacentTerritory(t1);
    t2->addAdjacentTerritory(t3);
    t3->addAdjacentTerritory(t2);
    
    // Create test players
    Player* p1 = new Player("Player1");
    Player* p2 = new Player("Player2");
    
    // 1. Test Deploy Order
    std::cout << "\nTest 1: Deploy Order\n";
    std::cout << "--------------------------------------\n";
    
    p1->addTerritory(1, "Territory1");
    t1->setOwner(p1);
    p1->setReinforcementPool(10);
    
    DeployOrder* deploy = new DeployOrder(p1, t1, 5);
    deploy->attach(logger);
    
    std::cout << "Testing Deploy Order validation...\n";
    if (deploy->validate()) {
        std::cout << "Deploy Order validation successful\n";
        if (deploy->execute()) {
            std::cout << "Deploy successful: " << deploy->getEffect() << std::endl;
        }
    }
    
    // 2. Test Advance Order
    std::cout << "\nTest 2: Advance Order\n";
    std::cout << "--------------------------------------\n";
    
    p2->addTerritory(2, "Territory2");
    t2->setOwner(p2);
    t2->setArmies(5);
    
    AdvanceOrder* advance = new AdvanceOrder(p2, t2, t3, 3);
    advance->attach(logger);
    
    std::cout << "Testing Advance Order validation...\n";
    if (advance->validate()) {
        std::cout << "Advance Order validation successful\n";
        if (advance->execute()) {
            std::cout << "Advance successful: " << advance->getEffect() << std::endl;
        }
    }
    
    // 3. Test Bomb Order
    std::cout << "\nTest 3: Bomb Order\n";
    std::cout << "--------------------------------------\n";
    
    t3->setOwner(p2);
    t3->setArmies(10);
    
    BombOrder* bomb = new BombOrder(p1, t3);
    bomb->attach(logger);
    
    std::cout << "Testing Bomb Order validation...\n";
    if (bomb->validate()) {
        std::cout << "Bomb Order validation successful\n";
        if (bomb->execute()) {
            std::cout << "Bomb successful: " << bomb->getEffect() << std::endl;
        }
    }
    
    // 4. Test Blockade Order
    std::cout << "\nTest 4: Blockade Order\n";
    std::cout << "--------------------------------------\n";
    
    BlockadeOrder* blockade = new BlockadeOrder(p1, t1);
    blockade->attach(logger);
    
    std::cout << "Testing Blockade Order validation...\n";
    if (blockade->validate()) {
        std::cout << "Blockade Order validation successful\n";
        if (blockade->execute()) {
            std::cout << "Blockade successful: " << blockade->getEffect() << std::endl;
        }
    }
    
    // 5. Test Airlift Order
    std::cout << "\nTest 5: Airlift Order\n";
    std::cout << "--------------------------------------\n";
    
    AirliftOrder* airlift = new AirliftOrder(p1, t1, t2, 2);
    airlift->attach(logger);
    
    std::cout << "Testing Airlift Order validation...\n";
    if (airlift->validate()) {
        std::cout << "Airlift Order validation successful\n";
        if (airlift->execute()) {
            std::cout << "Airlift successful: " << airlift->getEffect() << std::endl;
        }
    }
    
    // 6. Test Negotiate Order
    std::cout << "\nTest 6: Negotiate Order\n";
    std::cout << "--------------------------------------\n";
    
    NegotiateOrder* negotiate = new NegotiateOrder(p1, p2);
    negotiate->attach(logger);
    
    std::cout << "Testing Negotiate Order validation...\n";
    if (negotiate->validate()) {
        std::cout << "Negotiate Order validation successful\n";
        if (negotiate->execute()) {
            std::cout << "Negotiate successful: " << negotiate->getEffect() << std::endl;
        }
    }
    
    // 7. Test OrdersList functionality
    std::cout << "\nTest 7: OrdersList\n";
    std::cout << "--------------------------------------\n";
    
    OrdersList* ordersList = new OrdersList();
    ordersList->attach(logger);
    
    ordersList->add(deploy);
    std::cout << "Added Deploy order\n";
    ordersList->add(advance);
    std::cout << "Added Advance order\n";
    
    std::cout << "Moving order from position 1 to 0\n";
    ordersList->move(1, 0);
    
    // Clean up allocated memory
    delete ordersList;
    delete negotiate;
    delete airlift;
    delete blockade;
    delete bomb;
    delete p1;
    delete p2;
    delete t1;
    delete t2;
    delete t3;
    
    std::cout << "\nOrder Execution testing completed.\n";
    std::cout << "Check gamelog.txt for logging output.\n";
}

int main() {
    std::cout << "\n===== Starting Orders Testing =====\n";
    
    testOrderExecution();
    
    std::cout << "\n===== Orders Testing Completed =====\n";
    return 0;
}
*/
