# Go Foundation

## Software Requirements
- Go tools (https://go.dev/dl)
    - Verification
        ```shell
        go version
        ```
- Visual Studio Code (or any other editor)
- Go Extension for VS Code (https://marketplace.visualstudio.com/items?itemName=golang.Go)

## Why Go?
- Simplicity
    - ONLY 25 keywords
    - No access modifiers (public, private, protected etc)
    - No reference types (Everything is a value)
    - No pointer arithmatic support in the language 
    - No classes (only structs)
    - No inheritance (only composition)
    - No exceptions (only errors)
    - No try..catch..finally construct
    - No implicit type conversions
- Managed Concurrency
    - lightweight concurrency model (goroutines) - 4KB
    - Built in scheduler
    - Concurrency support is built in the language itself
        - "go" keyword, "chan" data type, channel operator (<-), range construct, select-case constructs
    - Standart Library support
        - "sync" package
        - "sync/atomic" package
- Close to hardware
    - No VM, No JIT
    - Less startup time
    - One build per deployment platform
    - Builtin support for cross compilation

## Standard Library Docs 
- https://pkg.go.dev/std 

## Compilation
```shell
go build <file_name.go>
```

## Compile & Execute
```shell
go run <file_name.go>
```

## Get the list of suppported platforms
```shell
go tool dist list
```

## Get the env variables & values
```shell
go env
```
```shell
go env <var_1> <var_2>
```

## Env variables for cross compilation
- GOOS
- GOARCH

## Cross compilation
```shell
GOOS=windows GOARCH=amd64 go build 01-hello-world.go
```

## Data Types
- string
- bool
- integers
    - int8
    - int16
    - int32
    - int64
    - int
- unsigned integers
    - uint8
    - uint16
    - uint32
    - uint64
    - uint
- floating points
    - float32
    - float64
- complex
    - complex64 ( real[float32] + imaginary[float32] )
    - complex128 ( real[float64] + imaginary[float64] )
- alias
    - byte (alias for unsigned int)
    - rune (alias for unicode code point)

### Zero values
| Data Type | Zero value |
------------ | ------------- |
|int family     | 0 |
|uint family    | 0 |
|complex family | (0+0i) |
|string         | "" (empty string) |
|bool           | false |
|byte           | 0 |
|interface      | nil |
|pointer        | nil |
|function       | nil |
|struct         | struct instance |

## Variables
### Function Scope
- Can use ":="
- CANNOT have unused variables

### Package Scope
- Cannot use ":="
- CAN have unused variables

## Constructs
### if else
### switch case
### for

## Functions
    - functions can have more than one return results
        - named results
    - anonymous functions
        - cannot have names
        - can be declared in another function
        - must be immediately executed
    - Higher Order Functions
        - functions can be treated like data
        - functions can be assigned to variables
        - functions can be passed as arguments
        - functions can be returned as return values

## Collections
### Array
- Fixed sized typed collection

### Slice
- Varying sized typed collection
- Maintains a pointer to an underlying array
- functions
    - len()
    - append()

### Map
- Varying sized typed collection of key/value pairs

## Error Handling
- errors are just values
- not thrown but returned from a function
- by convention, error objects implement "error" interface
- creating an error
    - errors.New()
    - fmt.Errorf()
    - custome type implementing the "error" interface

## Panic & Recovery
- A panic is a state of the application where the application execution cannot proceed in the forward direction
- functions
    - panic
    - recover

## Modules & Packages
### Module
- Any code that has to be versioned & deployed together
- Any folder that has the go.mod file
- go.mod file
    - manifest file for the module
        - module name
            - advisable to have the complete repo path as the module name
        - go runtime version
        - dependencies
#### Create a go.mod file
```shell
go mod init <module_name>
```

#### run a module
```shell
go run .
```

#### Create a build of a module
```shell
go build .
go build -o <output_file_name> .
```

#### Installing a 3rd party module
[ By default, the code is downloaded into the GOPATH/pkg folder ]
```shell
go get <module_name>
```

#### to update a dependency
```shell
go get -u <module_name>
```

#### Updating the references in go.mod file
```shell
go mod tidy
```

#### Download the dependencies documented in the go.mod file
```shell
go mod download
```

#### To localize the dependencies into a local "vendor" folder
```shell
go mod vendor
```

### Package
- Internal organization of a module
- typically a folder

## Structs
- Classes in Go

## Go Concurrency
### WaitGroup
- semaphore based counter (has the ability to block the execution of a function)
- internally maintains a counter and it can block the exeuction of a function until counter becomes 0

### Data Race
```shell
go run --race <program.go>
```
```shell
go build --race <program.go>
```

### Communication
- "Share memory by communicating" strategy
#### Channel (data type)
##### Declaration
```go
var <var_name> chan <data_type>
//ex:
var ch chan int
```
##### Initialization
```go
<var_name> = make(chan <data_type>)
// ex:
ch = make(chan int)
```
##### Combine Declaration & Initialization
```go
var ch chan int = make(chan int)
//OR
var ch = make(chan int)
//OR
ch := make(chan int)
```
##### Communication through the channel (using <- operation)
###### Send Operation
```go
ch <- 100
```
###### Receive Operation
```go
data := <- ch
```
