# CTFbot

A lightweight CTF game engine written in C for small VPS deployments (including 2 vCPU / 1 GB RAM). The core uses SQLite and OpenSSL only.

## Current MVP

- Per-player persistent challenge instances
- CSPRNG-backed randomized challenge material (`getrandom`)
- SHA-256, hex, and Caesar training challenges
- Hashes/values change on each reset/new instance, but remain stable while a player solves them
- Answers stored as SHA-256 verifiers rather than plaintext
- XP, solve counts, profiles, and top-10 leaderboard
- SQLite WAL mode
- CLI suitable for testing and as the game-engine boundary for the Discord adapter

> The `sha256` challenge intentionally uses a small generated training wordspace so it is a CTF puzzle, not a password-cracking system.

## Build

```bash
sudo apt update
sudo apt install -y build-essential libsqlite3-dev libssl-dev
make check
```

## CLI

```bash
./ctfbot init
./ctfbot start 123456789 sha256
./ctfbot active 123456789
./ctfbot reset 123456789 hex
./ctfbot submit 123456789 answer
./ctfbot profile 123456789
./ctfbot leaderboard
```

Set `CTFBOT_DB=/path/to/ctfbot.db` to choose the database location.

## Architecture

The engine is deliberately independent from Discord transport. Discord slash commands will map to these engine operations, keeping game state and verification testable without Discord or network access. The next adapter will expose `/challenge`, `/submit`, `/profile`, `/leaderboard`, and `/reset` while keeping the same engine.

## VPS target

The engine is a single native process with no Node.js, Redis, PostgreSQL, or Docker requirement. SQLite provides persistence with minimal memory overhead.
