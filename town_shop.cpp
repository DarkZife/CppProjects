#include <iostream>
#include <string>
#include <vector>

struct Item {
    std::string name;
    int price;
    int quantity;
};

struct Player {
    int gold;
    std::vector<Item> backpack;
};

void buyItem(Player& player, std::vector<Item>& shop) {
    std::cout << "Items available in the shop:\n";
    for (size_t i = 0; i < shop.size(); i++) {
        std::cout << i + 1 << ". " << shop[i].name << " - " << shop[i].price << " gold (Quantity: " << shop[i].quantity << ")\n";
    }

    int itemChoice, quantity;
    std::cout << "Enter the number of the item you want to buy: ";
    std::cin >> itemChoice;
    itemChoice--;

    if (itemChoice >= 0 && itemChoice < shop.size()) {
        std::cout << "Enter the quantity you want to buy: ";
        std::cin >> quantity;

        if (quantity > 0 && quantity <= shop[itemChoice].quantity) {
            int totalCost = quantity * shop[itemChoice].price;
            if (player.gold >= totalCost) {
                player.gold -= totalCost;
                shop[itemChoice].quantity -= quantity;
                player.backpack.push_back({shop[itemChoice].name, shop[itemChoice].price, quantity});
                std::cout << "You have purchased " << quantity << " " << shop[itemChoice].name << ". Your new gold balance: " << player.gold << " gold.\n";
            } else {
                std::cout << "You don't have enough gold to make this purchase.\n";
            }
        } else {
            std::cout << "Invalid quantity or item choice.\n";
        }
    } else {
        std::cout << "Invalid item choice.\n";
    }
}

void sellItem(Player& player, std::vector<Item>& shop) {
    std::cout << "Items available in your backpack:\n";
    for (size_t i = 0; i < player.backpack.size(); i++) {
        std::cout << i + 1 << ". " << player.backpack[i].name << " - " << player.backpack[i].price << " gold (Quantity: " << player.backpack[i].quantity << ")\n";
    }

    int itemChoice, quantity;
    std::cout << "Enter the number of the item you want to sell: ";
    std::cin >> itemChoice;
    itemChoice--;

    if (itemChoice >= 0 && itemChoice < player.backpack.size()) {
        std::cout << "Enter the quantity you want to sell: ";
        std::cin >> quantity;

        if (quantity > 0 && quantity <= player.backpack[itemChoice].quantity) {
            int totalValue = quantity * player.backpack[itemChoice].price;
            player.gold += totalValue;
            player.backpack[itemChoice].quantity -= quantity;

            if (player.backpack[itemChoice].quantity == 0) {
                player.backpack.erase(player.backpack.begin() + itemChoice);
            }

            std::cout << "You have sold " << quantity << " " << player.backpack[itemChoice].name << " for " << totalValue << " gold. Your new gold balance: " << player.gold << " gold.\n";
        } else {
            std::cout << "Invalid quantity or item choice.\n";
        }
    } else {
        std::cout << "Invalid item choice.\n";
    }
}

int main() {
    Player player;
    player.gold = 50;
    
    std::vector<Item> blacksmithItems = {
        {"Basic Shield", 3, 5},
        {"Sword", 10, 3},
        {"Chainmail Armor", 15, 2}
    };
    
    std::vector<Item> innItems = {
        {"Healing Potion", 5, 10},
        {"Elixir of Strength", 8, 5},
        {"Antidote", 4, 8}
    };
    
    std::vector<Item> generalGoodsItems = {
        {"Bread", 2, 20},
        {"Torch", 1, 15},
        {"Rope", 3, 7}
    };

    while (true) {
        std::cout << "Main Menu:\n";
        std::cout << "1. Enter Town\n";
        std::cout << "2. Check Backpack\n";
        std::cout << "3. Logout\n";
        int choice;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 1) {
            while (true) {
                std::cout << "Town Menu:\n";
                std::cout << "1. Inn\n";
                std::cout << "2. Blacksmith\n";
                std::cout << "3. General Goods\n";
                std::cout << "4. Check Backpack\n";
                std::cout << "5. Leave Town\n";
                std::cout << "Enter your choice: ";
                std::cin >> choice;

                if (choice == 1) {
                    std::cout << "Inn Menu:\n";
                    std::cout << "1. Stay at the Inn for 10 gold coins a night\n";
                    std::cout << "2. Open the shop\n";
                    std::cout << "3. Leave the Inn\n";
                    std::cout << "Enter your choice: ";
                    std::cin >> choice;

                    if (choice == 1) {
                        if (player.gold >= 10) {
                            player.gold -= 10;
                            std::cout << "Goodnight! You stayed at the Inn.\n";
                            std::cout << "Backpack Contents:\n";
                            for (const Item& item : player.backpack) {
                                std::cout << item.name << " - " << item.quantity << " (Total Value: " << item.price * item.quantity << " gold)\n";
                    }
                    std::cout << "Gold: " << player.gold << " gold\n";
                            return 0;
                        } else {
                            std::cout << "You don't have enough gold to stay at the Inn.\n";
                        }
                    } else if (choice == 2) {
                        buyItem(player, innItems);
                    } else if (choice == 3) {
                        // Leave Inn
                    } else {
                        std::cout << "Invalid choice.\n";
                    }
                } else if (choice == 2) {
                    std::cout << "Blacksmith Menu:\n";
                    std::cout << "1. Buy\n";
                    std::cout << "2. Sell\n";
                    std::cout << "3. Leave\n";
                    std::cout << "Enter your choice: ";
                    std::cin >> choice;

                    if (choice == 1) {
                        buyItem(player, blacksmithItems);
                    } else if (choice == 2) {
                        sellItem(player, blacksmithItems);
                    } else if (choice == 3) {
                        // Leave Blacksmith
                    } else {
                        std::cout << "Invalid choice.\n";
                    }
                } else if (choice == 3) {
                    std::cout << "General Goods Menu:\n";
                    std::cout << "1. Buy\n";
                    std::cout << "2. Sell\n";
                    std::cout << "3. Leave\n";
                    std::cout << "Enter your choice: ";
                    std::cin >> choice;

                    if (choice == 1) {
                        buyItem(player, generalGoodsItems);
                    } else if (choice == 2) {
                        sellItem(player, generalGoodsItems);
                    } else if (choice == 3) {
                        // Leave General Goods
                    } else {
                        std::cout << "Invalid choice.\n";
                    }
                } else if (choice == 4) {
                    std::cout << "Backpack Contents:\n";
                    for (const Item& item : player.backpack) {
                        std::cout << item.name << " - " << item.quantity << " (Total Value: " << item.price * item.quantity << " gold)\n";
                    }
                    std::cout << "Gold: " << player.gold << " gold\n";
                } else if (choice == 5) {
                    break; // Leave Town
                } else {
                    std::cout << "Invalid choice.\n";
                }
            }
        } else if (choice == 2) {
            std::cout << "Backpack Contents:\n";
            for (const Item& item : player.backpack) {
                std::cout << item.name << " - " << item.quantity << " (Total Value: " << item.price * item.quantity << " gold)\n";
            }
            std::cout << "Gold: " << player.gold << " gold\n";
        } else if (choice == 3) {
            std::cout << "You have logged out. Exiting the program...\n";
            return 0;
        } else {
            std::cout << "Invalid choice.\n";
        }
    }

    return 0;
}
