\name{engel}
\alias{engel}
\title{Engel Data}
\description{
  Engel food expenditure data used in Koenker and Bassett(1982).
  This is a regression data set consisting of 235 observations on
  income and expenditure on food for Belgian working class households.
}
\usage{data(engel)}
\format{A data frame containing 235 observations on 2 variables
  \describe{
    \item{income}{annual household income in Belgian francs}
    \item{foodexp}{annual household food expenditure in Belgian francs}
  }
}
\references{
  Koenker, R. and Bassett, G (1982)
  Robust Tests of Heteroscedasticity based on Regression Quantiles;
  \emph{Econometrica} \bold{50}, 43--61.
}
\examples{
## See also    demo("engel1")
##             --------------

data(engel)
plot(engel, log = "xy",
     main = "'engel' data  (log - log scale)")
plot(log10(foodexp) ~ log10(income), data = engel,
     main = "'engel' data  (log10 - transformed)")
taus <- c(.15, .25, .50, .75, .95, .99)
rqs <- as.list(taus)
for(i in seq(along = taus)) {
  rqs[[i]] <- rq(log10(foodexp) ~ log10(income), tau = taus[i], data = engel)
  lines(log10(engel$income), fitted(rqs[[i]]), col = i+1)
}
legend("bottomright", paste("tau = ", taus), inset = .04,
       col = 2:(length(taus)+1), lty=1)
}
\keyword{datasets}
