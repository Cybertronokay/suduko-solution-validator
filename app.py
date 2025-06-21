from flask import Flask, request, jsonify
from flask_cors import CORS
import subprocess
import os

app = Flask(__name__)
CORS(app)  # This line enables CORS

@app.route('/validate', methods=['POST'])
def validate():
    try:
        data = request.get_json()
        grid = data.get('grid')

        if not isinstance(grid, list):
            return jsonify({'message': 'Grid is not a list'}), 400

        if len(grid) != 9:
            return jsonify({'message': f'Grid should have 9 rows, found {len(grid)}'}), 400

        for i, row in enumerate(grid):
            if not isinstance(row, list) or len(row) != 9:
                return jsonify({'message': f'Row {i + 1} is invalid (length: {len(row)})'}), 400

        # Write to file
        with open('input.txt', 'w') as f:
            for row in grid:
                f.write(' '.join(str(num) for num in row) + '\n')

        # Run C++ validator
        result = subprocess.run(['main.exe'], capture_output=True, text=True)
        return jsonify({'message': result.stdout.strip()})

    except Exception as e:
        return jsonify({'message': f'Unexpected error: {str(e)}'}), 500


if __name__ == '__main__':
    app.run(debug=True)
