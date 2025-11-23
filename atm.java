/*
Card
- name
- expirationDate
- cvv
- pin

Account
- accountNumber
- balance
- card:Card
- withdraw(amount):boolean
- deposit(amount):boolean
- validatePin(inputPin):boolean

ATMContext
- currentState:ATMState
- acccount:AccountNumber
- 


ATMState
- IdleState
    - next()
        if(card inserted) -> HasCardState
        else -> IdleState
- HasCardState
    - next()
        if (pin validated) -> selectedOperationState
        else if (wrong pin) -> EjectCardState
        else -> HasCardState

- SelectedOperationState
    - next()
        if(withdraw selected) -> TransactionState
        else if(deposit selected) -> TransactionState
        else if(change pin selected) -> EjectCardState
        else -> SelectedOperationState

- TransactionState
    - next()
        if(transaction complete) -> EjectCardState
        else -> TransactionState
- EjectCardState
    - next()
        return to IdleState

*/