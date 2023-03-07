FROM faurealexis/epitech-tools

WORKDIR /app

COPY . .

RUN make re

CMD ["/app/myftp", "210", "bonus"]

