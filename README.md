
# 📜 Presentation


In Philosophers, we're dealing with the Dining Philosophers problem at Ecole 42. It's a really interesting challenge. Imagine a group of philosophers sitting around a table, thinking and eating spaghetti. The issue? They have to share a limited number of forks. Our task is to make sure they can eat without any problems or fighting over forks. We need to create a fair system for managing resources, so each philosopher can enjoy their meal and thoughts. This project helps us learn a lot about programming and managing resources effectively.


# 📖 Rules

There is two versions :

- **Mandatory Part :**
    - Each philosopher should be a thread.
    - There is one fork between each pair of philosophers.        Therefore, if there are several philosophers, each philosopher has a fork on their left side and a fork on their right side. If there is only one philosopher, there should be only one fork on the table.
    - To prevent philosophers from duplicating forks, you should protect the forks state with a mutex for each of them
- **Bonus Part :**
    - All the forks are put in the middle of the table.
    - They have no states in memory but the number of available forks is represented by a semaphore.
    - Each philosopher should be a process. But the main process should not be a philosopher.


# 🛠 How to use

- **Mandatory Part :**
    - `make -C philo/ && cd philo/`
- **Bonus Part :**
    - `make -C philo_bonus/ && cd philo_bonus/`

Then for both part the arguments are the following ones :
- **number_of_philosophers:** The number of philosophers and also the number of forks.
- **time_to_die (in milliseconds):** If a philosopher didn’t start eating time_to_die milliseconds since the beginning of their last meal or the beginning of the simulation, they die.
- **time_to_eat (in milliseconds):** The time it takes for a philosopher to eat. During that time, they will need to hold two forks.
- **time_to_sleep (in milliseconds):** The time a philosopher will spend sleeping.
- **number_of_times_each_philosopher_must_eat (optional argument):** If all philosophers have eaten at least number_of_times_each_philosopher_must_eat times, the simulation stops. If not specified, the simulation stops when a philosopher dies.

# 📒 Exemples

`./philo 4 410 200 200`

`./philo 4 310 200 100`

`./philo 5 800 200 200 7`

`./philo 1 400 200 200`

