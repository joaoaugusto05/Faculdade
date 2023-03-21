from scipy import stats
from statsmodels.stats.proportion import proportions_ztest
import pandas as pd
import numpy as np
init = 8
jump = 6
df = pd.read_csv('Titanic.csv')
df = df[(df['PassengerId'] > init - 1) & ((df['PassengerId']-init)%jump ==0)]

Survived = df[df['Survived'] == 1]
Dead = df[df['Survived'] == 0]
t, p = stats.ttest_ind(a=Survived['Age'].to_list(), b=Dead['Age'].to_list(), equal_var=False)
print(p)
print("Idade: ", stats.ttest_ind(Survived['Age'],Dead['Age'], equal_var = False))
print("Tarifa: ", stats.ttest_ind(Survived['Fare'],Dead['Fare'], equal_var = False))


Mulheres_vivas = Survived[Survived['Sex'] == 'female']
Homens_vivos = Survived[Survived['Sex'] == 'male']


df['Survived'] = df['Survived'].map({1:'Survived',0:'Not Survived'})
contingency_table = pd.crosstab(df.Survived,df.Sex)
tab = pd.crosstab(df.Survived,df.Sex).apply(lambda r:r/r.sum(),axis=0)



total_proportion_survived = (df.Survived == "Survived").mean()
num_female = df[df.Sex=="female"].shape[0]
num_male = df[df.Sex=="male"].shape[0]

prop = df.groupby("Sex")["Survived"].agg([lambda z: np.mean(z=="Survived"), "size"])
prop.columns = ['proportions_survived','total_counts']


variance = total_proportion_survived * (1 - total_proportion_survived)
standard_error = np.sqrt(variance * (1 / prop.total_counts.female + 1 / prop.total_counts.male))
print("Sample Standard Error",standard_error)

best_estimate = (prop.proportions_survived.female - prop.proportions_survived.male)
print("The best estimate is",best_estimate)
hypothesized_estimate = 0
test_stat = (best_estimate-hypothesized_estimate) / standard_error
print("Computed Test Statistic is",test_stat)