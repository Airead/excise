o <- seq(10*2*pi, 0, -0.1)
a <- 0
b <- 1

r <- a + b*o
x <- r*cos(o)
y <- r*sin(o)
plot(x, y, type = 'l')