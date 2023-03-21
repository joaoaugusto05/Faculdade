import pandas as pd
import scipy.stats as stats
import statistics as s



def sys_sampling(start, step):
    # Trocar o path do dataset para o caso de voces':w
    data = pd.read_csv('Titanic.csv');

    start = start - 2
    sampled_data = data[(data.index >= start) & (((data.index - start) % step) == 0)]

    return sampled_data

# Trocar o start e o step para o caso de voces
data = sys_sampling(8, 6)
print(data)
survivers = data[data['Survived'] == 1]
non_survivers = data[data['Survived'] == 0]
age = data['Age'].tolist()
fare = data['Fare'].tolist()


survivers_age = survivers['Age'].tolist()
non_survivers_age = non_survivers['Age'].tolist()

t, p = stats.ttest_ind(a=survivers_age, b=non_survivers_age, equal_var=False)
print(f'Test ages: t = {t} p = {p}')

survivers_fare = survivers['Fare'].tolist()
non_survivers_fare = non_survivers['Fare'].tolist()


t, p = stats.ttest_ind(a=survivers_fare, b=non_survivers_fare, equal_var=False)
print(f'Test fare: t = {t} p = {p}')

t, p = stats.levene(survivers_age, non_survivers_age)
print(f'Levene test age: t = {t} p = {p}')

t, p = stats.levene(survivers_fare, non_survivers_fare)
print(f'Levene test fare: t = {t} p = {p}')




