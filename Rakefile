# frozen_string_literal: true

require "fileutils"

FEATURE_FILES =
  %w[core pair input debug array_sum bisect imos prime tally cumulative_sum_2d imos_2d]
    .freeze
BUNDLE_OUTPUT = "dist/main.cpp"
CPP_STANDARD = "-std=gnu++20"
CPP_INCLUDES = "-I."

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

desc "Bundle feature headers into one file"
task bundle: "features:bundle"

namespace :tests do
  desc "Build and run all feature tests"
  task :run do
    test_sources = Dir.glob("tests/test_*.cpp")
    raise "No tests found" if test_sources.empty?

    build_dir = File.join("build", "tests")
    FileUtils.mkdir_p(build_dir)

    test_sources.each do |source|
      exe_name = File.basename(source, ".cpp")
      exe_path = File.join(build_dir, exe_name)
      cmd = ["g++", CPP_STANDARD, CPP_INCLUDES, source, "-o", exe_path]
      sh cmd.join(" ")
      sh exe_path
    end
  end
end

desc "Run tests"
task test: "tests:run"
