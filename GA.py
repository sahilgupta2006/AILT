import random


def roulette_selection(population, fitnesses):
    total = sum(fitnesses)

    if total <= 0:
        return random.choice(population)

    r = random.uniform(0, total)
    s = 0

    for individual, fitness in zip(population, fitnesses):
        s += fitness
        if s >= r:
            return individual

    return population[-1]


def tournament_selection(population, fitness, k=3):
    candidates = random.sample(population, min(k, len(population)))
    return max(candidates, key=fitness)


def single_point_crossover(a, b):
    p = random.randint(1, len(a) - 1)
    return a[:p] + b[p:], b[:p] + a[p:]


def two_point_crossover(a, b):
    p, q = sorted(random.sample(range(1, len(a)), 2))
    c1 = a[:p] + b[p:q] + a[q:]
    c2 = b[:p] + a[p:q] + b[q:]
    return c1, c2


def uniform_crossover(a, b):
    c1 = []
    c2 = []

    for x, y in zip(a, b):
        if random.random() < 0.5:
            c1.append(x)
            c2.append(y)
        else:
            c1.append(y)
            c2.append(x)

    return c1, c2


def arithmetic_crossover(a, b):
    alpha = random.random()
    c1 = [alpha * x + (1 - alpha) * y for x, y in zip(a, b)]
    c2 = [alpha * y + (1 - alpha) * x for x, y in zip(a, b)]
    return c1, c2


def ox_crossover(a, b):
    n = len(a)
    p, q = sorted(random.sample(range(n), 2))

    c1 = [None] * n
    c2 = [None] * n

    c1[p:q] = a[p:q]
    c2[p:q] = b[p:q]

    remaining1 = [x for x in b if x not in c1]
    remaining2 = [x for x in a if x not in c2]

    j = 0
    for i in range(n):
        if c1[i] is None:
            c1[i] = remaining1[j]
            j += 1

    j = 0
    for i in range(n):
        if c2[i] is None:
            c2[i] = remaining2[j]
            j += 1

    return c1, c2


def pmx_crossover(a, b):
    n = len(a)
    p, q = sorted(random.sample(range(n), 2))

    c1 = [None] * n
    c2 = [None] * n

    c1[p:q] = a[p:q]
    c2[p:q] = b[p:q]

    for i in range(p, q):
        if b[i] not in c1:
            j = i
            while p <= j < q:
                x = a[j]
                j = b.index(x)
            c1[j] = b[i]

        if a[i] not in c2:
            j = i
            while p <= j < q:
                x = b[j]
                j = a.index(x)
            c2[j] = a[i]

    for i in range(n):
        if c1[i] is None:
            c1[i] = b[i]

        if c2[i] is None:
            c2[i] = a[i]

    return c1, c2


def bit_flip_mutation(x):
    x = x[:]
    i = random.randrange(len(x))
    x[i] = 1 - x[i]
    return x


def swap_mutation(x):
    x = x[:]
    i, j = random.sample(range(len(x)), 2)
    x[i], x[j] = x[j], x[i]
    return x


def inversion_mutation(x):
    x = x[:]
    i, j = sorted(random.sample(range(len(x)), 2))
    x[i:j] = reversed(x[i:j])
    return x


def scramble_mutation(x):
    x = x[:]
    i, j = sorted(random.sample(range(len(x)), 2))
    part = x[i:j]
    random.shuffle(part)
    x[i:j] = part
    return x


def random_reset_mutation(x, low, high):
    x = x[:]
    i = random.randrange(len(x))
    x[i] = random.randint(low, high)
    return x


def gaussian_mutation(x, sigma=1):
    x = x[:]
    i = random.randrange(len(x))
    x[i] += random.gauss(0, sigma)
    return x


def genetic_algorithm(
    create_individual,
    fitness,
    crossover,
    mutate,
    population_size=50,
    generations=100,
    mutation_rate=0.05,
    selection="roulette",
    maximize=True
):
    population = [
        create_individual()
        for _ in range(population_size)
    ]

    for _ in range(generations):

        population.sort(
            key=fitness,
            reverse=maximize
        )

        new_population = [population[0][:]]

        while len(new_population) < population_size:

            fitnesses = [fitness(x) for x in population]

            if selection == "roulette":
                p1 = roulette_selection(population, fitnesses)
                p2 = roulette_selection(population, fitnesses)
            else:
                p1 = tournament_selection(population, fitness)
                p2 = tournament_selection(population, fitness)

            c1, c2 = crossover(p1, p2)

            if random.random() < mutation_rate:
                c1 = mutate(c1)

            if random.random() < mutation_rate:
                c2 = mutate(c2)

            new_population.append(c1)

            if len(new_population) < population_size:
                new_population.append(c2)

        population = new_population

    population.sort(
        key=fitness,
        reverse=maximize
    )

    return population[0], fitness(population[0])

best, value = genetic_algorithm(
    create_individual,
    fitness,
    single_point_crossover,
    bit_flip_mutation,
    population_size=20,
    generations=50,
    mutation_rate=0.1
)

print(best)
print(decode(best))
print(value)