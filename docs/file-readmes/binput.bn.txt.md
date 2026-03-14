# binput.bn.txt Detailed Program Walkthrough

This file is the primary end-to-end test program for the language.

---

## 1) Program boundary lines

- First line: শুরু_প্রোগ্রাম
	- marks parser entry into program mode.
- Last line: শেষ_প্রোগ্রাম
	- marks parser completion boundary.

Without these markers, grammar rejects input at top level.

---

## 2) Primitive declarations section

Early lines declare and initialize:
- integer variable বয়স
- decimal variable ফ
- boolean variable সত্য_মিথ্যা
- char variable এ
- string variable বাক্য_উদাহরণ

What this tests:
- type tokens recognition
- literal parsing across all scalar types
- declaration+assignment semantics

---

## 3) Comment handling section

Comment lines enclosed by মন্তব্য ... মন্তব্য_শেষ test lexer exclusive COMMENT state.

Expectation:
- comment content contributes no parser tokens.

---

## 4) Input and echo section

Sequence:
1. declare ব্যবহারকারী_বয়স
2. print prompt
3. input into variable
4. print confirmation and value
5. declare ব্যবহারকারী_নাম
6. prompt, input, echo

What this tests:
- INPUT statement parsing
- runtime typed input conversion
- string handling and output

---

## 5) If/else branch section

Condition compares ব্যবহারকারী_বয়স with ১৮ and prints adult/teen message.

What this tests:
- relational expression parsing
- indentation-based suite parsing
- boolean condition enforcement at runtime

---

## 6) While loop section

Loop:
- starts at গ = ০
- while গ ছোট ১০
- prints শর্মি
- increments গ

What this tests:
- while control-flow
- increment statement behavior
- repeated suite execution

---

## 7) Range-for loop section

ঘুরতে_থাক(ই) ১ থেকে ৩ prints loop variable each iteration.

What this tests:
- for-range grammar
- inclusive end behavior
- loop variable assignment each pass

---

## 8) Function definition and call section

Function যোগ_কর(গ):
- initializes যোগফল
- loops while গ ছোট ৬
- updates accumulator
- returns যোগফল

Then caller:
- declares উত্তর
- assigns via যোগ_কর(৩)
- prints উত্তর

What this tests:
- function table definition/lookup
- argument passing
- scope push/pop
- return signal propagation

---

## 9) Array section

Operations:
- declare typed array with initializer list
- read elements [0], [2]
- assign element [1] = 99
- read updated element
- compute length via দৈর্ঘ্য(...)

What this tests:
- array declaration
- initializer ordering
- bounds-safe element access/assignment
- builtin length lowering and execution

---

## 10) Second array + indexed loop section

Declares array ধ and iterates with আই as index.

What this tests:
- variable index in array access
- while-loop + array integration

---

## 11) Operator-heavy section

Declares এক্স and ওয়াই then computes:
- add, subtract, multiply, divide, modulo
- logical and/or/not via প/ক booleans
- increment/decrement statements

What this tests:
- arithmetic operator precedence and evaluation
- logical expression lowering to bool values

---

## 12) Math builtin section

Calls:
- শক্তি, বর্গমূল, ফ্লোর, সিল, পরম

What this tests:
- parser builtin node creation
- runtime numeric builtin dispatch
- TAC call lowering for builtins in IR mode

