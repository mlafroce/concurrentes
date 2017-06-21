#!/usr/bin/env bash
./db-server &
SERVER_PID=$!
./db-client < client1.in &
CLIENT1_PID=$!
./db-client < client2.in &
CLIENT2_PID=$!
./db-client < client3.in &
CLIENT3_PID=$!

sleep 1

kill -2 $CLIENT1_PID
kill -2 $CLIENT2_PID
kill -2 $CLIENT3_PID

kill -2 $SERVER_PID

