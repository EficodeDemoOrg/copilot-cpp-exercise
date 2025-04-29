graph LR
    subgraph Log Analyzer Application
        direction LR
        CLI[main.cpp / CLI Handler] --> PARSER[LogParser Module];
        PARSER -- Creates --> ENTRY[LogEntry Objects];
        CLI --> FILTER[LogFilter Module];
        ENTRY -- Consumed by --> FILTER;
        FILTER -- Creates --> FILTERED_ENTRY[Filtered LogEntry Objects];
        CLI --> REPORTER[LogReporter Module];
        FILTERED_ENTRY -- Consumed by --> REPORTER;
    end

    subgraph Inputs
        LOG_FILES[Sample Log Files (.log)];
    end

    subgraph Outputs
        CONSOLE[Console Output];
    end

    LOG_FILES --> PARSER;
    REPORTER --> CONSOLE;

    %% Styling (Optional)
    classDef data fill:#f9f,stroke:#333,stroke-width:2px;
    class ENTRY,FILTERED_ENTRY data;
    classDef module fill:#ccf,stroke:#333,stroke-width:2px;
    class PARSER,FILTER,REPORTER module;
    classDef io fill:#cfc,stroke:#333,stroke-width:2px;
    class LOG_FILES,CONSOLE io;
    classDef main fill:#fcc,stroke:#333,stroke-width:2px;
    class CLI main;