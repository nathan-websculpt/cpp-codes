/*
    Drill: Expression Parser / AST Evaluator

    -------------------------------------------------------------------------
    The Problem
    -------------------------------------------------------------------------

    Build a small arithmetic expression parser that takes a string such as:

        3 + 4 * (2 - 1)

    and turns it into an expression tree / AST, then evaluates it.

    This is a tree drill, but not a "binary tree from scratch" drill. The tree
    exists because the problem naturally requires hierarchical structure:
    operators have operands, parentheses create nested sub-expressions, and
    precedence determines tree shape.

    Example expression tree for:

        3 + 4 * (2 - 1)

    Conceptually:

            +
           / \
          3   *
             / \
            4   -
               / \
              2   1

    -------------------------------------------------------------------------
    Scope of Code to Complete
    -------------------------------------------------------------------------

    Minimum version:

    1. Read an expression from std::string or std::getline(std::cin, input).
    2. Tokenize the input into numbers, operators, parentheses, and end marker.
    3. Parse the expression using recursive descent.
    4. Build an AST representing:
        - number literals
        - binary operators: +, -, *, /
        - parenthesized sub-expressions
    5. Evaluate the AST and print the result.
    6. Print useful parse/evaluation errors for invalid input.

    Suggested grammar:

        expression  := term (('+' | '-') term)*
        term        := factor (('*' | '/') factor)*
        factor      := number | '(' expression ')'

    Optional later expansion:

    - unary minus: -5 or -(3 + 2)
    - exponentiation: 2 ^ 3
    - variables: x + 3
    - assignment: x = 10
    - pretty-print the tree
    - constant folding optimization

    -------------------------------------------------------------------------
    Core Skills
    -------------------------------------------------------------------------

    - Recursive descent parsing
    - Operator precedence and associativity
    - AST / expression-tree design
    - Tree traversal
    - Input validation
    - Error reporting
    - Clean separation between:
        - tokenization
        - parsing
        - evaluation
        - output/reporting

    Key design question:

        Does parsing print errors directly, throw exceptions, return std::optional,
        return std::expected-like result, or store diagnostics?

    For this drill, exceptions are acceptable for early learning, but try to keep
    parsing/evaluation logic separate from console output.

    -------------------------------------------------------------------------
    Modern C++ Angle
    -------------------------------------------------------------------------

    Prefer RAII and ownership-aware tree construction.

    Simple first version:

        struct Expr {
            virtual ~Expr() = default;
            virtual double evaluate() const = 0;
        };

        struct NumberExpr : Expr {
            double value {};
            double evaluate() const override;
        };

        struct BinaryExpr : Expr {
            char op {};
            std::unique_ptr<Expr> left;
            std::unique_ptr<Expr> right;

            double evaluate() const override;
        };

    This makes ownership explicit:

        - A BinaryExpr owns its left child.
        - A BinaryExpr owns its right child.
        - The root std::unique_ptr<Expr> owns the whole AST.
        - Destroying the root destroys the full tree recursively.

    Alternative modern design:

        Use std::variant instead of virtual inheritance.

    That avoids vtables and dynamic polymorphism, but requires more careful
    handling because recursive variants usually need indirection somewhere.

    Example idea:

        struct NumberExpr;
        struct BinaryExpr;

        using Expr = std::variant<NumberExpr, BinaryExpr>;

    However, BinaryExpr cannot directly contain Expr by value without creating
    an infinitely recursive type. You still need some form of indirection, such
    as std::unique_ptr<Expr>.

    -------------------------------------------------------------------------
    Dynamic Memory / Performance Notes
    -------------------------------------------------------------------------

    The straightforward AST version usually performs one heap allocation per
    expression node:

        std::make_unique<NumberExpr>(...)
        std::make_unique<BinaryExpr>(...)

    That is clean and idiomatic for the first version.

    Later optimization paths:

    1. Arena allocation:
        Allocate many nodes from one contiguous memory arena, then destroy all
        nodes at once when parsing is complete.

    2. Vector-backed node storage:
        Store nodes in std::vector<Node> and refer to children by index instead
        of pointer.

            struct Node {
                enum class Kind { Number, Binary };
                Kind kind {};
                double value {};
                char op {};
                std::size_t left {};
                std::size_t right {};
            };

    This improves locality because nodes live closer together in memory instead
    of being scattered across the heap.

    Do not optimize too early. First make the parser correct and readable.

    -------------------------------------------------------------------------
    Example Input
    -------------------------------------------------------------------------

        3 + 4 * (2 - 1)

    -------------------------------------------------------------------------
    Example Output
    -------------------------------------------------------------------------

        Input:  3 + 4 * (2 - 1)
        Result: 7

        Tree:
        +
          3
          *
            4
            -
              2
              1

    -------------------------------------------------------------------------
    Definition of Done
    -------------------------------------------------------------------------

    The drill is complete when:

    - valid expressions evaluate correctly
    - operator precedence works
    - parentheses work
    - invalid expressions produce useful errors
    - AST ownership is clear and leak-free
    - the parser logic is not tangled with console output
*/

#include <iostream>

int main() {
    std::cout << "works\n";
}