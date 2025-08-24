FROM gcc:latest AS builder

WORKDIR /app

COPY . .

RUN g++ -std=c++17 main.cpp LogParser.cpp -o main -pthread

# FROM debian:slim

FROM ubuntu:latest

WORKDIR /app

COPY --from=builder /app/main .

EXPOSE 8080

CMD ["./main"]