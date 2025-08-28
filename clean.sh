#!/bin/bash
# Скрипт для полной очистки директории build (debug и release)

set -e

rm -rf build/debug build/release

# Можно добавить очистку других временных файлов, если потребуется

echo "Директории build/debug и build/release удалены."
