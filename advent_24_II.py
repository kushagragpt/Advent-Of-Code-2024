#!/usr/bin/env python
import re
from enum import Enum

class Op(Enum):
    AND = 1
    OR = 2
    XOR = 3


class Gate:
    def __init__(self, op, arg1, arg2):
        self.op = Op[op]
        self.arg1 = arg1
        self.arg2 = arg2

    def __repr__(self):
        return f"Gate(op={self.op} arg1={self.arg1}, arg2={self.arg2})"


with open("input.txt", "r") as file:
    lines = [line.strip() for line in file]

cmd_re = re.compile(r'([\d\w]+) (AND|OR|XOR) ([\d\w]+) -> ([\d\w]+)')
wire_re = re.compile(r'([\d\w]+): (\d)')

blank = lines.index('')
wires = {w: int(v) for w, v in (wire_re.match(line).groups() for line in lines[:blank])}
lines = lines[blank + 1:]

gates = {}

for line in lines:
    if (match := cmd_re.match(line)) is None:
        raise RuntimeError(f"Couldn't parse: {line}")
    opn1, op, opn2, out = match.groups()
    print(f"op: {op:6} opn1: {opn1:3} opn2: {str(opn2):4} out: {out}")
    if out in gates:
        raise RuntimeError(f"Multiple gates output to {out}")
    gates[out] = Gate(op, opn1, opn2)


def calc_gate(gates, wires, output):
    if output in wires:
        return wires[output]
    gate = gates[output]
    arg1 = calc_gate(gates, wires, gate.arg1)
    arg2 = calc_gate(gates, wires, gate.arg2)
    match gate.op:
        case Op.AND:
            result = arg1 & arg2
            op = '&'
        case Op.OR:
            result = arg1 | arg2
            op = '|'
        case Op.XOR:
            result = arg1 ^ arg2
            op = '^'
    #print(f"Gate {output} = {gate.arg1} {op} {gate.arg2} = {arg1} {op} {arg2} = {result}")
    wires[output] = result
    return result


def calc_circuit(gates, inputs):
    inputs = inputs.copy()
    gate_inputs = set(a for args in ((g.arg1, g.arg2) for g in gates.values()) for a in args if a is not None)
    gate_outputs = set(gates.keys())
    free_outputs = gate_outputs.difference(gate_inputs)

    for out in free_outputs:
        calc_gate(gates, inputs, out)
    return inputs


def int_from_wires(wires):
    res = 0
    for k, v in wires:
        shift = int(k[1:])
        res += v << shift
    return res


z_wires = calc_circuit(gates, wires)
z_wires = ((k, v) for k, v in z_wires.items() if k.startswith('z'))
outval = int_from_wires(z_wires)
print(f"Final result: {outval:b} = {outval}")
in_x = int_from_wires((k, v) for k, v in wires.items() if k.startswith('x'))
in_y = int_from_wires((k, v) for k, v in wires.items() if k.startswith('y'))
actual_z = in_x + in_y
print(f"{in_x} + {in_y} should be {actual_z}, not {outval}")
#exit(0)


def calc_adder(gates, x, y):
    inputs = {f'x{b:02}': (x & (1 << b)) >> b for b in range(45)}
    inputs.update({f'y{b:02}': (y & (1 << b)) >> b for b in range(45)})
    output = calc_circuit(gates, inputs)
    z_wires = ((k, v) for k, v in output.items() if k.startswith('z'))
    outval = 0
    for k, v in z_wires:
        shift = int(k[1:])
        outval += v << shift
    return outval


def get_used_wires(gates, output):
    if output not in gates:
        return set()
    gate = gates[output]
    return set([output]).union(get_used_wires(gates, gate.arg1), get_used_wires(gates, gate.arg2))


def test_circuit(gates, swapped, depth):
    for i in range(45):
        x = (1 << i)
        y = x
        res = calc_adder(gates, x, y)
        if x + x != res:
            break
        y = 0
        res = calc_adder(gates, x, y)
        if x != res:
            break
        for j in range(45):
            y = (1 << j)
            res = calc_adder(gates, x, y)
            if x + y != res:
                break
        else:
            x, y = in_x, in_y
            res = calc_adder(gates, x, y)
            if actual_z != res:
                break
    else:
        i = 0
        print(f"{depth} Intense check of {swapped}")
        pat1 = sum(1 << x for x in range(0, 45, 2))
        pat2 = sum(3 << x for x in range(0, 45, 4))
        pat3 = sum(15 << x for x in range(0, 45, 8))
        pat4 = sum(255 << x for x in range(0, 45, 16))
        pat5 = sum(65535 << x for x in range(0, 45, 32))
        inv1 = sum(1 << x for x in range(1, 45, 2))
        inv2 = sum(3 << x for x in range(2, 45, 4))
        inv3 = sum(15 << x for x in range(4, 45, 8))
        inv4 = sum(255 << x for x in range(8, 45, 16))
        inv5 = sum(65535 << x for x in range(16, 45, 32))
        patterns = (pat1, pat2, pat3, pat4, pat5, inv1, inv2, inv3, inv4, inv5)
        combos = ((p1, p2) for p1 in patterns for p2 in patterns if int.bit_length(p1 + p2) < 46)
        for x, y in combos:
            res = calc_adder(gates, x, y)
            if res != x + y:
                break
        else:
            print(f"Adder appears to be working correctly.")
            return None
    print(f"{depth} Adder broke at {x} + {y} = {res} (!= {x + y})")
    return (i, x, y)


def check_circuit(gates, swapped, depth=1):
    print(f"{depth} Checking swapped: {swapped}")
    res = test_circuit(gates, swapped, depth)
    if res is None:
        return [swapped]
    if len(swapped) == 4:
        return None
    i, x, y = res
    # We broke at bit i, which makes us assume that all the previous gates are correct
    ok_outputs = set(f'z{b:02}' for b in range(i))
    ok_outputs = ok_outputs.union(*(get_used_wires(gates, o) for o in ok_outputs))

    bad_outputs = set(gates.keys()).difference(ok_outputs)
    already_swapped = (a for s in swapped for a in s)
    candidates = list(bad_outputs.difference(already_swapped))

    results = []
    for i, swap1 in enumerate(candidates):
        used_wires1 = get_used_wires(gates, swap1)
        for swap2 in candidates[i + 1:]:
            used_wires2 = get_used_wires(gates, swap2)
            if swap1 in used_wires2 or swap2 in used_wires1:
                # Can't swap, would create loop
                continue
            #print(f"Swapping {swap1} and {swap2}")
            g = gates.copy()
            g[swap1], g[swap2] = g[swap2], g[swap1]
            if x + y == calc_adder(g, x, y):
                print(f"{depth} Found possible swap: {swap1} <-> {swap2}")
                res = check_circuit(g, swapped + [(swap1, swap2)], depth + 1)
                if res is not None:
                    results += res
                #print(f"Swap lead to nowhere, searching next")
    print(f"{depth} Found {len(results)} possible swappings in {swapped}")
    return results


results = check_circuit(gates, [])
res = '\n'.join(','.join(sorted(x for s in swapped for x in s)) for swapped in results)
print(res)