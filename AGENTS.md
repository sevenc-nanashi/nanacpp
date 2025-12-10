# AGENTS.md

## ライブラリ実装の流れ

- `./features/[feature_name].hpp`に新しい機能を実装
- `./tests/test_[feature_name].cpp`に対応するテストコードを実装
- `./README.md`の「機能一覧」に新しい機能の説明を追加
- `rake test[feature_name]`でテストを実行して動作確認
- `rake test`で全体の回帰テストを実行して影響範囲を確認

## 実装詳細

- ドキュメントは日本語で書くこと
- C++23標準に準拠すること
