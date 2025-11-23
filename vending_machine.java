/**

Vending Machine Simulation

The C++ program simulates a vending machine that allows user to select and purchase
items. It includes features such as display

Class


Inventory
- items
- addItem()

VendingMachineContext
- currentState
- inventory
- itemCode
- paymentStrategy


VendingMachineState

1) IdleState 
   - next()
        if(out of stock) ->OutOfStockState
        else if(money inserted) -> HasMoneyState 
        else ->IdleState 

2) HasMoneyState
    -next()
        if(selection made) ->SelectionState
        else if(money returned) ->IdleState
        else -> HasMoneyState

3) SelectionState
    - next()
        if(item available) -> DispenseState
        else -> OutOfStockState

4) DispenseState
    - next()
        return to IdleState

5) OutOfStockState
    - next()
        return to IdleState


**/