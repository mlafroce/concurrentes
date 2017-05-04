#!/bin/bash

echo "1. Kill tp"
killall tp
echo "2. Free semaphores"
bash free_semaphores.sh
echo "3. Free Shared Memory"
bash free_sharedmemory.sh