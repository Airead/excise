setwd("~/study/git-proj/excise/lushi")

library(reshape2)

data <- read.csv('cards.csv');

getCost <- function(cost, headers) {
  ret <- data[data$cost == cost & data$card_type == 4, headers]
  return(ret)
}

ans <- function(cost) {
  headers = c('card_name', 'atk', 'health')
  ret <- getCost(cost, headers)
  freq <- table(ret$atk, ret$health)
  print(freq)
  m <- melt(freq)
  print(m[order(m$value), ])
  return(ret)
}
