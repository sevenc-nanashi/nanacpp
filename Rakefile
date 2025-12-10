# frozen_string_literal: true

require "fileutils"

def alias_task(**tasks)
  tasks.each do |new_name, old_name|
    desc "Alias for #{old_name}"
    task new_name, [*Rake.application[old_name].arg_names] do |t, args|
      Rake::Task[old_name].invoke(*args.to_a)
    end
  end
end

FEATURE_FILES =
  %w[core pair input debug array_sum bisect imos prime tally cumulative_sum_2d imos_2d interval_set]
    .freeze
BUNDLE_OUTPUT = "dist/main.cpp"

task :default => %i[test bundle]

namespace :features do
  desc "Bundle feature headers into a single file for competitive programming"
  task :bundle, [:output] do |_, args|
    output = args[:output] || BUNDLE_OUTPUT
    FileUtils.mkdir_p(File.dirname(output))

    File.open(output, "w") do |bundle|
      bundle.puts "// https://github.com/sevenc-nanashi/nanacpp"
      main = File.open("./main.cpp")
      main
        .take_while { |line| !line.start_with?("// ! features") }
        .each { |line| bundle.print(line) }

      FEATURE_FILES.each do |name|
        path = File.join("features", "#{name}.hpp")
        content = File.read(path)
        filtered_lines =
          content.each_line.reject do |line|
            stripped = line.strip
            stripped == "#pragma once" ||
              stripped.start_with?('#include "features/')
          end

        bundle.puts "\n// ----- #{path} -----"
        filtered_lines.each { |line| bundle.print(line) }
      end
      bundle.puts "\n// ----- main.cpp -----"

      main.each { |line| bundle.print(line) }
    end

    puts "Bundled features into #{output}"
  end
end

namespace :tests do
  desc "Build and run all feature tests"
  task :run, [:pattern] do |_, args|
    test_sources = Dir.glob("tests/test_*.cpp")
    raise "No tests found" if test_sources.empty?

    if args[:pattern]
      pattern = Regexp.new(args[:pattern])
      test_sources.select! { |src| File.basename(src) =~ pattern }
      raise "No tests match the pattern #{args[:pattern]}" if test_sources.empty?
    end

    options = File.read("./compile_flags.txt").strip.split("\n")

    build_dir = File.join("build", "tests")
    FileUtils.mkdir_p(build_dir)

    test_sources.each_with_index do |source, index|
      exe_name = File.basename(source, ".cpp")
      exe_path = File.join(build_dir, exe_name)
      cmd = ["g++", *options, source, "-o", exe_path]
      iputs "[#{index + 1}/#{test_sources.size}] Building and running #{source}..."
      sh cmd.join(" ")
      sh exe_path
      sputs "#{exe_name} passed."
    end
  end
end

task :tests do
  raise "Please specify a subtask. Make sure you quoted like `rake 'test[interval_set]'` because shell treats the argument as a glob pattern otherwise."
end

desc "Run tests"
alias_task test: "tests:run", bundle: "features:bundle"

def iputs(msg)
  if $stdout.tty?
    puts "\e[34m#{msg}\e[0m"
  else
    puts msg
  end
end
def sputs(msg)
  if $stdout.tty?
    puts "\e[32m#{msg}\e[0m"
  else
    puts msg
  end
end
