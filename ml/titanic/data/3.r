setwd("~/study/git-proj/excise/ml/titanic/data")
train <- read.csv("~/study/git-proj/excise/ml/titanic/data/train.csv")
test <- read.csv("~/study/git-proj/excise/ml/titanic/data/test.csv")

train$Child <- 0
train$Child[train$Age < 18] <- 1

train$Fare2 <- '30+'
train$Fare2[train$Fare < 30 & train$Fare >= 20] <- '20-30'
train$Fare2[train$Fare < 20 & train$Fare >= 10] <- '10-20'
train$Fare2[train$Fare < 10] <- '<10'

library(rpart)
library(rattle)
library(rpart.plot)
library(RColorBrewer)


fit <- rpart(Survived ~ Pclass + Sex + Age + SibSp + Parch + Fare + Embarked, data=train, method="class")

fancyRpartPlot(fit)

prediction = predict(fit, test, type = 'class')
submit = data.frame(PassengerId = test$PassengerId, Survived = prediction)
write.csv(submit, file = 'myfirstdtree.csv', row.names = FALSE)
