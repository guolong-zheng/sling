import re

def remove_redudent(inv_set):
    new_set = {}
    regex = re.compile('fv![0-9]+')
    for inv in inv_set:
        match = regex.findall(inv)
        i = 0
        for x in match:
            inv = inv.replace(x, "fv"+str(i))
            i = i + 1
        new_set.add(inv)
    return new_set
