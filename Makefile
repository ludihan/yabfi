.PHONY = clean build
build:
	go build -o yabfi ./src

clean:
	rm yabfi

