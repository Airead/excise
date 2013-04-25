lsf <- function() {
  files <- list.files(".")
  files
}

m <- 2
q <- 11

T <- c(3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 8, 9, 7, 9, 3)
t <- function(num, T, m, q) {
    r <- 0
    for (i in num:(num+m-1)) {
        r <- 10*r + T[i+1]
    }
    r %% q
}

P <- c(2, 6)
p <- t(0, P, m, q)

ts <- NULL
x <- 0:(length(T) - m)
for (i in x)
  ts <- c(ts, t(i, T, m, q))
