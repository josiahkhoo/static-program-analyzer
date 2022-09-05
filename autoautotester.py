import argparse
import os

# Parser
from collections import Counter

parser = argparse.ArgumentParser(description="Runs autotester")
parser.add_argument("--autotester_path", help="Autotester path", required=True)
parser.add_argument("--test_dir", help="Tests folder", required=True)
parser.add_argument("--os", help="Tests folder", choices=["mac", "windows"], required=True)
parser.add_argument("--debug", help="Debug flag", choices=["true", "false"], default=False)
args = parser.parse_args()

# Test arguments
autotester_path: str = args.autotester_path
test_dir_arg: str = args.test_dir
os_type: str = args.os
debug: str = args.debug

# Scripts
# Comment out tests that you don't want to test
test_array = (
    # ("Entities Only", "entities_only"),
    # ("Semantic Errors", "semantic_errors"),
    # ("Syntax Errors", "syntax_errors"),
    ("Sprint 1", "sprint_1"),
)

overall_passed_test_cases = 0
overall_failed_test_cases = 0

for test in test_array:
    test_name = test[0]
    test_dir = test[1]
    source_path = f"{test_dir_arg}/{test_dir}/test_{test_dir}_source.txt"
    queries_path = f"{test_dir_arg}/{test_dir}/test_{test_dir}_queries.txt"
    print(source_path, queries_path)
    output_path = f"{test_dir_arg}/out.xml"
    print(f"--- Running {test_name} Test ---")
    command = f"{autotester_path} {source_path} {queries_path} {output_path}"
    if os_type == 'windows':
        command = command.replace("/", "\\")
        if not debug:
            command += "> nul"
        output_path = output_path.replace("/", "\\")
    else:
        if not debug:
            command += "> /dev/null"
    os.system(command)
    with open(output_path) as f:
        output = f.read()
        text_chunks = Counter(output.split())
        passed_test_cases = text_chunks['<passed/>']
        failed_test_cases = text_chunks['<failed>']
        overall_passed_test_cases += passed_test_cases
        overall_failed_test_cases += failed_test_cases
        print(f"Passed: {passed_test_cases}, Failed: {failed_test_cases}")

print("=== Test Summary ===")
print(f"Total Passed: {overall_passed_test_cases}")
print(f"Total Failed: {overall_failed_test_cases}")

if overall_failed_test_cases > 0:
    exit(1)

exit(0)
