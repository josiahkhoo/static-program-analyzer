# Testing the SPA

## Folder Structure

Test cases are structured based on the category it belongs to.

```
├── clause_and_pattern
│   ├── test_clause_and_pattern_queries.txt
│   └── test_clause_and_pattern_source.txt
├── entities_only
│   ├── test_entities_only_queries.txt
│   ├── test_entities_only_source.txt
│   └── test_entities_only_source_annotated.txt
├── follows_follows_t
│   ├── test_follows_follows_t_queries.txt
│   └── test_follows_follows_t_source.txt
├── modifies_p
│   ├── test_modifies_p_queries.txt
│   └── test_modifies_p_source.txt
├── modifies_s
│   ├── test_modifies_s_queries.txt
│   └── test_modifies_s_source.txt
├── out.xml
├── parent_parent_t
│   ├── test_parent_parent_t_queries.txt
│   └── test_parent_parent_t_source.txt
├── patterns_only
│   ├── test_patterns_only_queries.txt
│   └── test_patterns_only_source.txt
├── semantic_errors
│   ├── test_semantic_errors_queries.txt
│   └── test_semantic_errors_source.txt
├── syntax_errors
│   ├── test_syntax_errors_queries.txt
│   └── test_syntax_errors_source.txt
├── uses_p
│   ├── test_uses_p_queries.txt
│   └── test_uses_p_source.txt
└── uses_s
    ├── test_uses_s_queries.txt
    └── test_uses_s_source.txt
```

## Naming

To support the `autoautotester.py` script. You need to name and store your test cases in a specific manner.
For a given `<dir-name>`, name your queries as `test_<dir-name>_queries.txt` and source as `test_<dir-name>_source.txt`.
Then store the queries and source under the directory `<dir-name>`.