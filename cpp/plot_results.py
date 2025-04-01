import matplotlib.pyplot as plt
import pandas as pd

# Charger les résultats
data = pd.read_csv("results.txt")

# Tracer le graphe
plt.figure(figsize=(8,5))
plt.plot(data["Threads"], data["ExecutionTime"], marker='o', linestyle='-')

# Ajouter des labels et un titre
plt.xlabel("Number of threads")
plt.ylabel("Execution Time (s)")
plt.title("Execution time depending on threads number")
plt.grid(True)

# Sauvegarder et afficher
plt.savefig("execution_time_plot.png")
plt.show()

