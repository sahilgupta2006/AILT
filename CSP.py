def csp_solve(variables, domains, neighbors, constraint):
    assignment = {}

    def select_mrv():
        unassigned = [v for v in variables if v not in assignment]
        return min(unassigned, key=lambda v: len(domains[v]))

    def backtrack():
        if len(assignment) == len(variables):
            return True

        var = select_mrv()

        for value in domains[var][:]:

            valid = True

            for neigh in neighbors[var]:
                if neigh in assignment:
                    if not constraint(var, value, neigh, assignment[neigh]):
                        valid = False
                        break

            if not valid:
                continue

            assignment[var] = value

            removed = []
            failed = False

            for neigh in neighbors[var]:
                if neigh in assignment:
                    continue

                new_domain = []

                for x in domains[neigh]:
                    if constraint(neigh, x, var, value):
                        new_domain.append(x)
                    else:
                        removed.append((neigh, x))

                domains[neigh] = new_domain

                if not domains[neigh]:
                    failed = True
                    break

            if not failed and backtrack():
                return True

            for neigh, x in removed:
                domains[neigh].append(x)

            del assignment[var]

        return False

    if backtrack():
        return assignment

    return None