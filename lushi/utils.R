# 法力曲线
# 6    5   4   4   3, 共22张，还有8张牌应变
# 二  三   四  五  六，能在对应回合70%抽得
## 速攻
## 铺场
## 控场
## 节奏

normal <- c(0,6,5,4,4,3);

# 第n回合能出n费卡
## 抽n张卡中没有1张属于集合m的卡的概率
noneMInN <- function(n, m) {
  return(prod((30-m):(30-m-n+1) / 30:(30-n+1)));
}
## 抽n张卡中至少有1张属于集合m的卡的概率
atLeastOneMInN <- function(n, m) {
  return(1-noneMInN(n, m));
}

# n费拿到m张核心卡
# 首抽拿到n张指定卡
# 第n回合共有法力水晶数
getRoundCost <- function(n) {
  return(sum(1:n));
}

# n张卡中，首抽至少能拿到1张的几率
zeroRound <- function(n) {
  return(1 - prod((30-n):(30-n-6) / 30:(30-6)));
}

# 至少拿一张的概率表
getAtLeastOneTable <- function() {
  matrix <- NULL;
  rows <- 3:20;
  cardNums <- 1:10;
  for (i in cardNums) {
    tmp <- sapply(rows, atLeastOneMInN, m=i);
    matrix <- cbind(matrix, tmp)
  }
  rownames(matrix) <- rows;
  colnames(matrix) <- cardNums;
  return(round(matrix*100, digits = 1));
}

# 开局无m,换n张,至少出一张m
startChange <- function(n, m) {
  totalCards <- 30-(3-n);
  
  return(1-prod((totalCards-m):(totalCards-m-n+1) / totalCards:(totalCards-n+1)));
}
