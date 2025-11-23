/**

Vending Machine Simulation

The C++ program simulates a vending machine that allows user to select and purchase
items. It includes features such as display

Class
Item
- name
- ItemType
- price

Shelf
- vector<Item> items
- code

Inventory
- vector<Shelf> shelves
- addItem()

Coin
- denomination

VendingMachine
- currentState
- inventory
- list<Coin> coins
- paymentStrategy
- insertCoin(Coin coin)
- setState(VendingMachineState st)

VendingMachineState

1) IdleState 
    - clickonInsertCoinButton() -> HasMoneyState

2) HasMoneyState

    - cancelorRefund() -> IdleState
    - coinInserted(VendingMachine vm, Coin coin) -> {
        vm.insertCoin(coin);
        vm.setState(new HasMoneyState());
    } 
    - clickOnStartProductSelectionButton(VendingMachine vm) -> {
        vm.setState(new SelectionState());
    }

3) SelectionState
    - chooseItem(VendingMachine vm,string code) -> { 
        Item item = vm.getInventory().getItemByCode(code);
        if(item.price > vm.getTotalInsertedAmount) -> IndsufficientFunds();
        else vm.setState(new DispenseState());
        
    - InsufficientFunds() -> HasMoneyState

4) DispenseState
    - dispenseItem() -> IdleState


**/