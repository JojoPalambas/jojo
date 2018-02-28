# -*- coding: utf-8 -*-
"""
Created on Tue Feb 27 18:01:25 2018

@author: gabri
"""

import random
import time
start = time.time()

"""

Data structure storing the grammar: list <tuple <string, list <list <bool, string>>>>
Example:
    [("operation",  [[(True, "operation"), (True, "operator"), (True, "operation")]]),
     ("operator",   [[(False, "+")],
                    [(False, "-")],
                    [(False, "*")],
                    [(False, "/")]])]

The data structure is a list, corresponding to the list of all the expendable tokens and their rules.
Each element of the list is a tuple:
    - The first element is a string, being the name of the current expandable token
    - The second element is the list of all the rules to expand the token.
      Each element is a list, being the list of words composing the rule.
      Each word of the rule is a tuple:
          - The first element is a bool, True if the word is an expandable token, else False
          - The second one is a string, the word itself

"""

"""
===============================================================================
============================ LIST MANAGEMENT ==================================
===============================================================================
"""

"""
Merges the two lists of strings and returns the merged list as follows:
    merge_list(["a", "b", "c"], ["1", "2"]) = ["a1", "a2", "b1", "b2", "c1", "c2"]
"""
def merge_list(l1, l2):
    if not l1:
        return l2
    if not l2:
        return l1
    ret = []
    for i in l1:
        for j in l2:
            ret.append(i + j)
    return ret

""" Otputs the content of the list, one element per line """
def out_list(l):
    for e in l:
        print(e)

"""
===============================================================================
=================== COMPLETE GRAMMAR POSSIBILITIES CHECK ======================
===============================================================================
"""

""" Returns the list of rules for the given token, None if the token matches no rule """
def get_rules(grammar, token):
    for e in grammar:
        if e[0] == token:
            return e[1]
    return None

""" Adds a token expansion to the histogram """
def histogram_add(histogram, token):
    cpy = histogram.copy()
    for i in range(len(cpy)):
        if cpy[i][0] == token:
            cpy[i] = (cpy[i][0], cpy[i][1] + 1)
            return cpy
    cpy.append((token, 1))
    return cpy

""" Checks if any value in the histogram is over the max value """
def histogram_check(histogram, max_value):
    for e in histogram:
        if e[1] > max_value:
            return True
    return False

""" Expands the given token with the grammar, and returns a list of all the possible strings """
def expand(grammar, token, histogram = [], max_depth = 2):
    if histogram_check(histogram, max_depth):
        return None
    rules = get_rules(grammar, token)
    if not rules:
        print("Rules not found for", token)
        return None
    ret = []
    for rule in rules:
        sub = subexpand_rule(grammar, rule, histogram, max_depth)
        if sub:
            ret += sub
    return ret

""" Expands the given rule with the grammar, and returns a list of all the possible strings """
def subexpand_rule(grammar, rule, histogram, max_depth):
    ret = []
    for word in rule:
        sub = subexpand_couple(grammar, word, histogram, max_depth)
        if not sub:
            return None
        ret = merge_list(ret, sub)
    return ret

""" Expands the given word with the grammar, and returns a list of all the possible strings """
def subexpand_couple(grammar, couple, histogram, max_depth):
    if not couple[0]:
        return [couple[1]]
    return expand(grammar, couple[1], histogram_add(histogram, couple[1]), max_depth)

"""
===============================================================================
========================= RANDOM GRAMMAR CHECK ================================
===============================================================================
"""

""" Picks a number between 0 and the given number, 0 included and the given number excluded """
def pick_index(n):
    if not n:
        return 0
    return random.randint(0, n - 1)

""" Picks a random rule is max_depth is not reached, else tries to find the best rule to finish the work fast """
def choose_rule(rules, depth, max_depth):
    # Puts terminal rules in term and non-terminal ones in nterm
    term = []
    nterm = []
    for rule in rules:
        x = False
        for (b, s) in rule:
            x = x or b
        if not x:
            term.append(rule)
        else:
            nterm.append(rule)
    # If there is only non-terminal rules
    if depth <= max_depth and nterm:
        return nterm[pick_index(len(nterm))]
    if depth > max_depth and term:
        return term[pick_index(len(term))]
    if not term:
        return nterm[pick_index(len(nterm))]
    return term[pick_index(len(term))]

""" Expands the token by picking random rules in the grammar """
def random_expand(grammar, token, depth = 0, max_depth = 5):
    rules = get_rules(grammar, token)
    if not rules:
        return None
    rule = choose_rule(rules, depth, max_depth)
    ret = ""
    for (b, s) in rule:
        if not b:
            ret += s
        else:
            ret += random_expand(grammar, s, depth + 1, max_depth)
    return ret

"""
===============================================================================
============================= PROGRAM BODY ====================================
===============================================================================
"""

expr = [("exp", [[(True, "exp"), (True, "op"), (True, "exp")],
                 [(True, "value")]]),
        ("op", [[(False, "+")],
                [(False, "-")],
                [(False, "*")],
                [(False, "/")],
                [(False, "%")]]),
        ("value", [[(False, "3")]])]

tiger = [("program", [[(True, "exp")],
                     [(True, "decs")]]),
         ("exp", [[(False, "nil")],
                  [(False, "5")],
                  [(False, "\"totor\"")],
                  [(True, "type-id"), (False, " ["), (True, "exp"), (False, "] of "), (True, "exp")],
                  [(True, "type-id"), (False, " {} ")],
                  [(True, "type-id"), (False, " {"), (True, "id"), (False, " = "), (True, "exp"), (False, "} ")],
                  [(True, "type-id"), (False, " {"), (True, "id"), (False, " = "), (True, "exp"), (False, ", "), (True, "id"), (False, " = "), (True, "exp"), (False, "} ")],
                  [(False, "new "), (True, "type-id")],
                  [(True, "lvalue")],
                  [(True, "id"), (False, "()")],
                  [(True, "id"), (False, "("), (True, "exp"), (False, ", "), (True, "exp"), (False, ")")],
                  [(True, "lvalue"), (False, "."), (True, "id"), (False, "()")],
                  [(True, "lvalue"), (False, "."), (True, "id"), (False, "("), (True, "exp"), (False, ", "), (True, "exp"), (False, ")")],
                  [(False, "-"), (True, "exp")],
                  [(True, "exp"), (True, "op"), (True, "exp")],
                  [(False, "("), (True, "exps"), (False, ")")],
                  [(False, "()")],
                  [(True, "lvalue"), (False, " := "), (True, "exp")],
                  [(False, "if "), (True, "exp"), (False, " then "), (True, "exp")],
                  [(False, "if "), (True, "exp"), (False, " then "), (True, "exp"), (False, " else "), (True, "exp")],
                  [(False, "while "), (True, "exp"), (False, " do "), (True, "exp")],
                  [(False, "for "), (True, "id"), (False, " := "), (True, "exp"), (False, " to "), (True, "exp"), (False, " do "), (True, "exp")],
                  [(False, "break")],
                  [(False, "let "), (True, "decs"), (False, " in "), (True, "exps"), (False, " end")],
                  [(False, "let "), (True, "decs"), (False, " in end")]]),
         ("lvalue", [[(True, "id")],
                     [(True, "lvalue"), (False, "."), (True, "id")],
                     [(True, "lvalue"), (False, "["), (True, "exp"), (False, "]")]]),
         ("exps", [[(True, "exp")],
                   [(True, "exp"), (False, " ; "), (True, "exps")]]),
         ("decs", [[(False, "")],
                   [(True, "decs2")]]),
         ("decs2", [[(True, "dec")],
                    [(True, "dec"), (False, " "), (True, "decs2")]]),
         ("dec", [[(False, "type "), (True, "id"), (False, " = "), (True, "ty")],
                  [(False, "class "), (True, "id"), (False, " extends "), (True, "type-id"), (False, " {"), (True, "classfields"), (False, "} ")],
                  [(False, "class "), (True, "id"), (False, " {"), (True, "classfields"), (False, "} ")],
                  [(True, "vardec")],
                  [(False, "function "), (True, "id"), (False, "("), (True, "tyfields"), (False, ") : "), (True, "type-id"), (False, " = "), (True, "exp")],
                  [(False, "function "), (True, "id"), (False, "("), (True, "tyfields"), (False, ") = "), (True, "exp")],
                  [(False, "function "), (True, "id"), (False, "("), (True, "tyfields"), (False, ") : "), (True, "type-id")],
                  [(False, "function "), (True, "id"), (False, "("), (True, "tyfields"), (False, ")")],
                  [(False, "import \"totor\"")]]),
         ("vardec", [[(False, "var "), (True, "id"), (False, " := "), (True, "exp")],
                     [(False, "var "), (True, "id"), (False, " : "), (True, "type-id"), (False, " := "), (True, "exp")]]),
         ("classfields", [[(False, "")],
                          [(True, "classfields2")]]),
         ("classfields2", [[(True, "classfield")],
                           [(True, "classfield"), (False, " "), (True, "classfields2")]]),
         ("classfield", [[(True, "vardec")],
                         [(False, "method "), (True, "id"), (False, "("), (True, "tyfields"), (False, ") : "), (True, "type-id"), (False, " = "), (True, "exp")],
                         [(False, "method "), (True, "id"), (False, "("), (True, "tyfields"), (False, ") = "), (True, "exp")]]),
         ("ty", [[(True, "type-id")],
                 [(False, "{"), (True, "tyfields"), (False, "}")],
                 [(False, "array of "), (True, "type-id")],
                 [(False, "class extends "), (True, "type-id"), (False, "{"), (True, "classfields"), (False, "}")],
                 [(False, "class {"), (True, "classfields"), (False, "}")]]),
         ("tyfields", [[(False, "")],
                       [(True, "tyfields2")]]),
         ("tyfields2", [[(True, "id"), (False, " : "), (True, "type-id")],
                        [(True, "id"), (False, " : "), (True, "type-id"), (False, ", "), (True, "tyfields2")]]),
         ("type-id", [[(False, "int")]]),
         ("id", [[(False, "x")]]),
         ("op", [[(False, "+")],
                 [(False, "-")],
                 [(False, "*")],
                 [(False, "/")],
                 [(False, "=")],
                 [(False, "<>")],
                 [(False, ">")],
                 [(False, "<")],
                 [(False, ">=")],
                 [(False, "<=")],
                 [(False, "&")],
                 [(False, "|")]])]

"""
DO NOT TRY THIS AT HOME:    
res = expand(tiger, "program", max_depth = 2)
out_list(res)
print(len(res))
"""

for i in range(10000):
    print(random_expand(tiger, "program"))
print(time.time() - start)